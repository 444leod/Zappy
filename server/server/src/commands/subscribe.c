/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** subscribed
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "lib.h"

/**
 * @brief Send the given packet to all the logged subscribers of the team
 * @details Send the given packet to all the logged subscribers of the team
 *        except the current client
 * @param team_uuid the team uuid
 * @param packet the packet
 * @param current_client the current client
*/
static void send_to_logged_subscribers(
    uuid_t team_uuid,
    packet_t *packet,
    client_t current_client)
{
    client_t client;
    team_t *team = get_team_by_uuid(team_uuid);
    users_t subscribers = get_team_subscribers(team);

    while (subscribers) {
        if (subscribers->user->is_logged && uuid_compare
            (subscribers->user->user_uuid, current_client->user->uuid) != 0) {
            client = get_client_by_uuid(subscribers->user->user_uuid);
            send_packet_to_client(client, packet);
        }
        subscribers = subscribers->next;
    }
}

/**
 * @brief Check if the command is valid
 * @details Check if the command is valid
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is valid
 * @return false if the command is not valid
 */
static bool is_command_valid(client_t client, char **command)
{
    if (tablen((void **)command) != 2) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NOT_LOGGED_IN, ""));
        return false;
    }
    return true;
}

/**
 * @brief Subscribe to a team
 * @details Subscribe to a team
 *
 * @param client the client
 * @param team the team
 */
static void subscribe_to_team(client_t client, team_t *team)
{
    packet_t *packet = build_team_packet(TEAM_SUBSCRIBED, team);

    server_event_user_subscribed(
        get_uuid_as_string(team->uuid),
        get_uuid_as_string(client->user->uuid)
    );
    add_to_list((void *)team, (node_t *)&client->user->subscribed_teams);
    add_packet_to_queue(&client->packet_queue, packet);
    send_to_logged_subscribers(team->uuid, packet, client);
}

/**
 * @brief /subscribe command handler
 * @details /subscribe command handler
 *
 * @param client the client
 * @param command the command
 */
void subscribe(client_t client, char **command)
{
    team_t *team = NULL;
    uuid_t team_uuid;

    if (!is_command_valid(client, command))
        return;
    get_uuid_from_string(command[1], team_uuid);
    team = get_team_by_uuid(team_uuid);
    if (!team) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_TEAM, command[1], TEAM));
        return;
    }
    if (is_user_subscribed_to_team(client->user, team_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(ALREADY_SUBSCRIBED, command[1], TEAM));
        return;
    }
    subscribe_to_team(client, team);
}
