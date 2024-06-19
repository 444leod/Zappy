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
 * @param socket_fd the socket to bind
 * @param port the port to bind to
*/
void bind_socket(const int socket_fd, const uint16_t port)
{
    struct sockaddr_in server_address;
    int bind_result = 0;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    bind_result = bind(socket_fd, (const struct sockaddr *)&server_address,
        sizeof(server_address));
    if (bind_result == -1)
        my_error(supercat(2, "bind failed: ", strerror(errno)));
}
