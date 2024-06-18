/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** listen_socket
*/

#include <arpa/inet.h>
#include "lib.h"

/**
 * @brief Listen a socket
 * @details Listen a socket with a given max_clients
 *
 * @param socket_fd the socket to listen
 * @param max_clients the max_clients to listen
*/
void listen_socket(const int socket_fd, const int max_clients)
{
    const int listen_result = listen(socket_fd, max_clients);

    if (listen_result == -1)
        my_error(supercat(2, "listen failed: ", strerror(errno)));
}
