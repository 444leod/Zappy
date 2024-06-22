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
static void my_clean_exit(const int status, const int fd)
{
    static int actual_fd = -1;

    if (status == -1) {
        actual_fd = fd;
        return;
    }
    if (actual_fd != -1)
        close(actual_fd);
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
void my_exit(const int status)
{
    my_clean_exit(status, 0);
}

/**
 * @brief Prepare the exit
 * @details Prepare the exit by sending the socket_fd to a store function.
*/
void prepare_exit(const int socket_fd)
{
    my_clean_exit(-1, socket_fd);
}
