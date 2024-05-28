/*
** EPITECH PROJECT, 2024
** get_reply
** File description:
** get_reply
*/

#include "data_structures.h"
#include <string.h>

/**
 * @brief Get the reply by uuid
 * @details Get the reply by uuid
 *
 * @param reply_uuid the reply uuid
 *
 * @return reply_t* the reply
 */
reply_t *get_reply_by_uuid(uuid_t reply_uuid)
{
    replies_t *replies = get_replies();
    replies_t tmp = *replies;

    while (tmp) {
        if (uuid_compare(tmp->reply->uuid, reply_uuid) == 0)
            return tmp->reply;
        tmp = tmp->next;
    }
    return NULL;
}
