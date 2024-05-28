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
    if (tablen((void **)command) > 2) {
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

static void list_team_subscribers(client_t client, team_t *team)
{
    users_t teams_subscribers = get_team_subscribers(team);
    user_information_t *user_info;

    if (!teams_subscribers) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(EMPTY_USER_LIST, "", TEAM));
        return;
    }
    while (teams_subscribers) {
        user_info = teams_subscribers->user;
        add_packet_to_queue(&client->packet_queue,
            build_userinfo_packet(USERS_LIST, user_info->username,
            user_info->user_uuid, user_info->is_logged));
        teams_subscribers = teams_subscribers->next;
    }
}

/**
 * @brief List all the teams the user is subscribed to
 * @details List all the teams the user is subscribed to
 *
 * @param client the client
 */
static void list_subscribed_teams(client_t client)
{
    teams_t *subscribed_teams = &client->user->subscribed_teams;
    teams_t tmp = (subscribed_teams ? *subscribed_teams : NULL);

    if (tmp == NULL) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(EMPTY_TEAM_LIST, "", TEAM));
        return;
    }
    while (tmp) {
        add_packet_to_queue(&client->packet_queue,
            build_team_packet(TEAM_LIST, tmp->team));
        tmp = tmp->next;
    }
}

/**
 * @brief Handle the subscribed command with a team given
 * @details Handle the subscribed command with a team given
 *
 * @param uuid the team uuid
 * @param client the client
 */
static void handle_team_subscribed_command(char *uuid, client_t client)
{
    team_t *team = NULL;
    uuid_t team_uuid;

    get_uuid_from_string(uuid, team_uuid);
    team = get_team_by_uuid(team_uuid);
    if (!team) {
        add_packet_to_queue(&client->packet_queue, build_custom_packet(
            INEXISTANT_TEAM, uuid, TEAM));
        return;
    }
    list_team_subscribers(client, team);
}

/**
 * @brief /subscribed command handler
 * @details /subscribed command handler
 *
 * @param client the client
 * @param command the command
 */
void subscribed(client_t client, char **command)
{
    if (!is_command_valid(client, command))
        return;
    if (command[1] != NULL && !is_uuid_valid(command[1])) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_TEAM, command[1], TEAM));
        return;
    }
    if (command[1] != NULL) {
        handle_team_subscribed_command(command[1], client);
    } else
        list_subscribed_teams(client);
}
