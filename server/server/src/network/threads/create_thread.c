/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_thread
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "lib.h"
#include <string.h>

/**
 * @brief Create a thread object
 * @details Create a thread object
 *
 * @param title the title of the thread
 * @param body the body of the thread
 * @param creator_uuid the creator of the thread
 *
 * @return thread_t* the thread
 */
thread_t *create_thread(title_t title, body_t body, uuid_t creator_uuid,
    uuid_t channel_uuid)
{
    thread_t *thread = my_malloc(sizeof(thread_t));

    memcpy(thread->title, title, strlen(title));
    memcpy(thread->body, body, strlen(body));
    memcpy(thread->creator_uuid, creator_uuid, sizeof(uuid_t));
    memcpy(thread->channel_uuid, channel_uuid, sizeof(uuid_t));
    thread->timestamp = time(NULL);
    uuid_generate(thread->uuid);
    server_event_thread_created(
        get_uuid_as_string(channel_uuid),
        get_uuid_as_string(thread->uuid),
        get_uuid_as_string(creator_uuid),
        my_strdup(title),
        my_strdup(body));
    add_to_list((void *)thread, (node_t *)get_threads());
    return thread;
}
