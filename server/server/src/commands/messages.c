/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** messages
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "macros.h"
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
    if (!is_uuid_valid(command[1])) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_USER, command[1], MESSAGE));
        return false;
    }
    return true;
}

/**
 * @brief List the messages
 * @details List the messages
 *
 * @param client the client
 * @param receiver_uuid the receiver uuid
 */
static void list_message(client_t client, uuid_t receiver_uuid)
{
    messages_t messages = get_messages_by_sender_and_receiver(
        client->user->uuid, receiver_uuid);
    packet_t *packet;

    if (!messages) {
        packet = build_custom_packet(EMPTY_MESSAGE_LIST, "", MESSAGE);
        add_packet_to_queue(&client->packet_queue, packet);
        return;
    }
    while (messages) {
        packet = build_message_packet(MESSAGES_LIST, messages->message);
        add_packet_to_queue(&client->packet_queue, packet);
        messages = messages->next;
    }
}

/**
 * @brief /messages command handler
 * @details /messages command handler
 *
 * @param client the client
 * @param command the command
 */
void messages(client_t client, char **command)
{
    uuid_t receiver_uuid;

    if (!is_command_valid(client, command))
        return;
    get_uuid_from_string(command[1], receiver_uuid);
    if (!get_user_by_uuid(receiver_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_USER, command[1], MESSAGE));
        return;
    }
    list_message(client, receiver_uuid);
}
