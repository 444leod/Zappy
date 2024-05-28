/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_channels
*/

#include "data_structures.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "debug.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include "lib.h"
#include "macros.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void print_intialized_channel(UNUSED channel_t *channel)
{
    DEBUG_PRINT("Channel loaded: %s (%s)\n", channel->name,
        get_uuid_as_string(channel->uuid));
}

/**
 * @brief Read the channels from the save file
 * @details Read the channels from the save file
 *
 * @param fd the file descriptor
*/
void read_channels(int fd)
{
    channel_t *new_channel;
    int rd = 0;

    while (1) {
        new_channel = my_malloc(sizeof(channel_t));
        rd = read(fd, new_channel, sizeof(channel_t));
        if (rd <= 0 || rd != sizeof(channel_t)) {
            my_free(new_channel);
            break;
        }
        if (get_team_by_uuid(new_channel->team_uuid) == NULL) {
            printf("team with uuid %s not found\n", new_channel->team_uuid);
            my_free(new_channel);
            continue;
        }
        print_intialized_channel(new_channel);
        add_to_list((void *)new_channel, (node_t *)get_channels());
    }
}

/**
 * @brief Init the channels linked list
 * @details Init the channels linked list using the .save/.channels file
*/
void init_channels(void)
{
    channels_t *channels = get_channels();
    int fd = open(SAVE_FOLDER".channels", O_RDONLY);

    *channels = NULL;
    DEBUG_PRINT("Init channels\n");
    if (fd == -1) {
        printf("channels: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("channels: Invalid magic number\n");
        close(fd);
        return;
    }
    read_channels(fd);
    close(fd);
}
