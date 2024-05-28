/*
** EPITECH PROJECT, 2024
** myreplys
** File description:
** create_reply
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "lib.h"
#include <string.h>

/**
 * @brief Create a reply object
 * @details Create a reply object
 *
 * @param name the name of the reply
 * @param description the description of the reply
 *
 * @return reply_t* the reply
 */
reply_t *create_reply(char *body, uuid_t creator_uuid, uuid_t thread_uuid)
{
    reply_t *reply = my_malloc(sizeof(struct reply_s));
    thread_t *thread = get_thread_by_uuid(thread_uuid);
    channel_t *channel = get_channel_by_uuid(thread->channel_uuid);

    memcpy(reply->body, body, strlen(body));
    memcpy(reply->creator_uuid, creator_uuid, sizeof(uuid_t));
    memcpy(reply->thread_uuid, thread_uuid, sizeof(uuid_t));
    memcpy(reply->team_uuid, channel->team_uuid, sizeof(uuid_t));
    uuid_generate(reply->uuid);
    add_to_list((void *)reply, (node_t *)get_replies());
    reply->timestamp = time(NULL);
    server_event_reply_created(
        get_uuid_as_string(thread_uuid),
        get_uuid_as_string(creator_uuid),
        my_strdup(body));
    return reply;
}
