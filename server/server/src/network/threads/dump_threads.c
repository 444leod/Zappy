/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_threads
*/

#include "linked_lists.h"
#include "data_structures.h"
#include "magic_number.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Dump the threads in a file
 * @details Dump the threads in a file
*/
void dump_threads(void)
{
    threads_t *threads = get_threads();
    threads_t tmp = *threads;
    int fd = open(SAVE_FOLDER".threads", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        write(fd, tmp->thread, sizeof(struct thread_s));
        tmp = tmp->next;
    }
}
