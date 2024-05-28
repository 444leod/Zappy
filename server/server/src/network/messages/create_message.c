/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_message
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "lib.h"
#include <string.h>

/**
 * @brief Create a message object
 * @details Create a message object
 *
 * @param message_body the body of the message
 * @param sender_uuid the sender of the message
 * @param receiver_uuid the receiver of the message
 *
 * @return message_t* the message
 */
message_t *create_message(body_t message_body, uuid_t sender_uuid,
    uuid_t receiver_uuid)
{
    message_t *message = my_malloc(sizeof(message_t));

    memcpy(message->body, message_body, strlen(message_body));
    memcpy(message->receiver_uuid, receiver_uuid, sizeof(uuid_t));
    memcpy(message->sender_uuid, sender_uuid, sizeof(uuid_t));
    uuid_generate(message->uuid);
    message->timestamp = time(NULL);
    add_to_list((void *)message, (node_t *)get_messages());
    server_event_private_message_sended(
        get_uuid_as_string(sender_uuid),
        get_uuid_as_string(receiver_uuid),
        my_strdup(message_body));
    return message;
}
