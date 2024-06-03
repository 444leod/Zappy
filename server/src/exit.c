/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** exit
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "garbage_collector.h"
#include "clients.h"

/**
 * @brief Clean exit
 * @details Clean exit by closing the fds (clients & socket)
 * and freeing all the memory
 *
 * @param status the status to exit with
 * @param fd the fd to close (if status == -1)
*/
static void my_clean_exit(int status, int fd)
{
    static int actualFd = -1;

    if (status == -1) {
        actualFd = fd;
        return;
    }
    if (actualFd != -1)
        close(actualFd);
    clear_clients();
    my_free_all();
    exit(status);
}

/**
 * @brief Exit the program
 * @details Exit the program by calling my_clean_exit with the status
 *
 * @param status the status to exit with
*/
void my_exit(int status)
{
    my_clean_exit(status, 0);
}

/**
 * @brief Prepare the exit
 * @details Prepare the exit by sending the socketFd to a store function.
*/
void prepare_exit(int socketFd)
{
    my_clean_exit(-1, socketFd);
}
