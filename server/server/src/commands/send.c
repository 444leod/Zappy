/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** login
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include <string.h>

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
    if (tablen((void **)command) != 3) {
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
 * @brief Check if the parameters are good
 * @details Check if the parameters are good (uuid and body)
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the parameters are good
 * @return false if the parameters are not good
 */
static bool is_param_good(client_t client, char **command)
{
    if (!is_uuid_valid(command[1])) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_USER, command[1], MESSAGE));
        return false;
    }
    if (strlen(command[2]) > MAX_BODY_LENGTH) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(BODY_TOO_LONG, ""));
        return false;
    }
    return true;
}

/**
 * @brief Create and send the message to the user
 * @details Create and send the message to the user
 *
 * @param client the client
 * @param receiver_uuid the receiver uuid
 * @param body the body
 */
static void create_and_send_to_user(client_t client, uuid_t receiver_uuid,
    body_t body)
{
    clients_t receivers = get_clients_by_user(
        get_user_by_uuid(receiver_uuid), NULL);
    message_t *message = create_message(body, client->user->uuid,
        receiver_uuid);

    add_packet_to_queue(&client->packet_queue,
        build_message_packet(MESSAGE_SENT, message));
    if (receivers) {
        send_packet_to_clients(receivers,
            build_message_packet(MESSAGE_RECEIVED, message));
    }
}

/**
 * @brief send command handler. Send a message to a user
 *
 * @param client the client
 * @param command the command
 */
void my_send(client_t client, char **command)
{
    body_t body;
    uuid_t receiver_uuid;
    user_t receiver;

    if (!is_command_valid(client, command) || !is_param_good(client, command))
        return;
    get_uuid_from_string(command[1], receiver_uuid);
    memset(body, 0, sizeof(body_t));
    strcpy(body, command[2]);
    receiver = get_user_by_uuid(receiver_uuid);
    if (!receiver) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_USER,
            command[1], MESSAGE));
        return;
    }
    create_and_send_to_user(client, receiver_uuid, body);
}
