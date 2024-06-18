/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** accept_client
*/

#include <arpa/inet.h>
#include "lib.h"

/**
 * @brief Accept a socket
 * @details Accept a socket and call a function with the clientFd
 *
 * @param socket_fd the socket to accept
*/
void accept_socket(const int socket_fd, void (*func)(int))
{
    int clientFd = 0;
    struct sockaddr_in client_address;
    socklen_t len = sizeof(client_address);

    clientFd = accept(socket_fd, (struct sockaddr *)&client_address, &len);
    if (clientFd < 0)
        my_error(supercat(2, "accept failed: ", strerror(errno)));
    func(clientFd);
}
