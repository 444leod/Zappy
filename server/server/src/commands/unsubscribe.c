/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** subscribed
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "lib.h"

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
 * @brief Unsubscribe to a team
 * @details Unsubscribe to a team
 *
 * @param client the client
 * @param team the team
 */
static void unsubscribe_to_team(client_t client, team_t *team)
{
    server_event_user_unsubscribed(
        get_uuid_as_string(team->uuid),
        get_uuid_as_string(client->user->uuid)
    );
    remove_from_list((void *)team, (node_t *)&client->user->subscribed_teams);
    add_packet_to_queue(
        &client->packet_queue,
        build_team_packet(TEAM_UNSUBSCRIBED, team)
    );
}

/**
 * @brief /unsubscribe command handler
 * @details /unsubscribe command handler
 *
 * @param client the client
 * @param command the command
 */
void unsubscribe(client_t client, char **command)
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
    if (!is_user_subscribed_to_team(client->user, team_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(NOT_SUBSCRIBED, command[1], TEAM));
        return;
    }
    unsubscribe_to_team(client, team);
}
