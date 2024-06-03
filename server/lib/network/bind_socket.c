/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** bind_socket
*/

#include <arpa/inet.h>
#include "lib.h"

/**
 * @brief Bind a socket
 * @details Bind a socket to a given port
 *
 * @param socketFd the socket to bind
 * @param port the port to bind to
*/
void bind_socket(int socketFd, int port)
{
    struct sockaddr_in serverAddress;
    int bindRes = 0;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
    bindRes = bind(socketFd, (const struct sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (bindRes == -1)
        my_error(supercat(2, "bind failed: ", strerror(errno)));
}
