/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** logout
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
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
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NOT_LOGGED_IN, ""));
        return false;
    }
    return true;
}

/**
 * @brief Logout the user
 * @details Logout the user
 *
 * @param client the client
 * @param command the command
 */
void logout(client_t client, char **command)
{
    user_t user = client->user;
    packet_t *pkt;

    if (!is_command_valid(client, command))
        return;
    client->user = NULL;
    pkt = build_userinfo_packet(USER_LOGGED_OUT,
        user->username, user->uuid, user->status);
    server_event_user_logged_out(get_uuid_as_string(user->uuid));
    if (get_clients_by_user(user, NULL) == NULL) {
        user->status = STATUS_NOT_LOGGED_IN;
        add_packet_to_queue(&client->packet_queue, pkt);
        send_packet_to_logged_users(pkt, NULL);
        return;
    }
    send_packet_to_logged_users(pkt, client);
}
