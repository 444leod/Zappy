/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_messages
*/

#include "linked_lists.h"
#include "data_structures.h"
#include "magic_number.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Dump the messages in a file
 * @details Dump the messages in a file
*/
void dump_messages(void)
{
    messages_t *messages = get_messages();
    messages_t tmp = *messages;
    int fd = open(SAVE_FOLDER".messages", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        write(fd, tmp->message, sizeof(struct message_s));
        tmp = tmp->next;
    }
}
