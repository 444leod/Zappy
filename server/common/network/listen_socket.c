/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** listen_socket
*/

#include <arpa/inet.h>
#include "lib.h"

/**
 * @brief Listen a socket
 * @details Listen a socket with a given maxClients
 *
 * @param socketFd the socket to listen
 * @param maxClients the maxClients to listen
*/
void listen_socket(int socketFd, int maxClients)
{
    int listenRes = listen(socketFd, maxClients);

    if (listenRes == -1)
        my_error(supercat(2, "listen failed: ", strerror(errno)));
}
