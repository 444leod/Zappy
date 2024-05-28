/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_channels
*/

#include "linked_lists.h"
#include "data_structures.h"
#include "magic_number.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Dump the channels in a file
 * @details Dump the channels in a file
*/
void dump_channels(void)
{
    channels_t *channels = get_channels();
    channels_t tmp = *channels;
    int fd = open(SAVE_FOLDER".channels", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        write(fd, tmp->channel, sizeof(struct channel_s));
        tmp = tmp->next;
    }
}
