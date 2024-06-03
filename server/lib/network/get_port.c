/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_port
*/

#include "lib.h"
#include <arpa/inet.h>

/**
 * @brief Get the port of a socket
 * @details Get the port of a socket and update the port variable
 *
 * @param fd the socket
 * @param port the port to update
*/
void get_port(int fd, int *port)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(fd, (struct sockaddr *)&sin, &len) == -1)
        my_error("getsockname");
    *port = ntohs(sin.sin_port);
}
