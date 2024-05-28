/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_channel
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "lib.h"
#include <string.h>

/**
 * @brief Create a channel object
 * @details Create a channel object
 *
 * @param title the title of the channel
 * @param description the description of the channel
 * @param team_uuid the team uuid
 *
 * @return channel_t* the channel
 */
channel_t *create_channel(title_t title, description_t description,
    uuid_t team_uuid)
{
    channel_t *channel = my_malloc(sizeof(channel_t));

    memcpy(channel->name, title, strlen(title));
    memcpy(channel->description, description, strlen(description));
    memcpy(channel->team_uuid, team_uuid, sizeof(uuid_t));
    uuid_generate(channel->uuid);
    add_to_list((void *)channel, (node_t *)get_channels());
    server_event_channel_created(get_uuid_as_string(team_uuid),
        get_uuid_as_string(channel->uuid), my_strdup(title));
    return channel;
}
