/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** user
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
    if (tablen((void **)command) != 2) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    return true;
}

/**
 * @brief User command handler, send user informations of a certain user
 * @details User command handler, send user informations of a certain user
 *
 * @param client the client
 * @param command the command
 */
void user(client_t client, char **command)
{
    user_t user;
    packet_t *pkt;
    uuid_t uuid;

    get_uuid_from_string(command[1], uuid);
    if (!is_command_valid(client, command))
        return;
    user = get_user_by_uuid(uuid);
    if (!user) {
        pkt = build_custom_packet(INEXISTANT_USER, command[1],
            USER_INFORMATION);
        add_packet_to_queue(&client->packet_queue, pkt);
        return;
    }
    pkt = build_userinfo_packet(USER_INFO, user->username, user->uuid,
        user->status);
    add_packet_to_queue(&client->packet_queue, pkt);
}
