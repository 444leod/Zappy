/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_message
*/

#include "data_structures.h"
#include <string.h>

/**
 * @brief Get the message by uuid
 * @details Get the message by uuid
 *
 * @param message_uuid the message uuid
 *
 * @return message_t* the message
 */
message_t *get_message_by_uuid(uuid_t message_uuid)
{
    messages_t *messages = get_messages();
    messages_t tmp = *messages;

    while (tmp) {
        if (uuid_compare(tmp->message->uuid, message_uuid) == 0)
            return tmp->message;
        tmp = tmp->next;
    }
    return NULL;
}
