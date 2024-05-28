/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** users
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"

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
    if (tablen((void **)command) != 1) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    return true;
}

/**
 * @brief Users command handler, send user informations of all users
 * @details Users command handler, send user informations of all users
 *
 * @param client the client
 * @param command the command
 */
void users(client_t client, char **command)
{
    user_t *users = get_users();
    user_t user = *users;
    packet_t *pkt;

    if (!is_command_valid(client, command))
        return;
    while (user) {
        pkt = build_userinfo_packet(USERS_LIST,
            user->username, user->uuid, user->status);
        add_packet_to_queue(&client->packet_queue, pkt);
        user = user->next;
    }
}
