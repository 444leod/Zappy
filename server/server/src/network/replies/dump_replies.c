/*
** EPITECH PROJECT, 2024
** myreplies
** File description:
** dump_replies
*/

#include "linked_lists.h"
#include "data_structures.h"
#include "magic_number.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Dump the replies in a file
 * @details Dump the replies in a file
*/
void dump_replies(void)
{
    replies_t *replies = get_replies();
    replies_t tmp = *replies;
    int fd = open(SAVE_FOLDER".replies", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        write(fd, tmp->reply, sizeof(struct reply_s));
        tmp = tmp->next;
    }
}
