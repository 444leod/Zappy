/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_socket
*/

#include <arpa/inet.h>
#include "lib.h"

/**
 * @brief Get a socket
 * @details Get a socket with the AF_INET and SOCK_STREAM parameters
 *
 * @return the socket
*/
int get_socket(void)
{
    const int socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        my_error(supercat(2, "get socket failed: ", strerror(errno)));
    return socketFd;
}
