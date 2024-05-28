/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_channels
*/

#include "data_structures.h"
#include "linked_lists.h"

/**
 * @brief Get the channels
 * @details Get the channels
 *
 * @return channels_t* the channels
 */
channels_t *get_channels(void)
{
    static channels_t channels = NULL;

    return &channels;
}

/**
 * @brief Get a channel by its team uuid
 * @details Get a channel by its team uuid
 *
 * @param team_uuid the team uuid
 *
 * @return channels_t the channels (linked list)
 */
channels_t get_channels_by_team(uuid_t team_uuid)
{
    channels_t *channels = get_channels();
    channels_t tmp = *channels;
    channels_t new_channels = NULL;

    while (tmp) {
        if (uuid_compare(tmp->channel->team_uuid, team_uuid) == 0)
            add_to_list((void *)tmp->channel, (node_t *)&new_channels);
        tmp = tmp->next;
    }
    return new_channels;
}
