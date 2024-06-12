/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** remove_client
*/

#include "clients.h"
#include "garbage_collector.h"

#include "zappy.h"
#include "lib.h"
#include "packet.h"
#include <unistd.h>

/**
 * @brief Destroy the fds
 * @details Destroy the fds of the client
 *
 * @param tmp the client
*/
static void destroy_fds(client_t tmp)
{
    if (tmp->fd != -1) {
        close(tmp->fd);
        tmp->fd = -1;
    }
}

/**
 * @brief Remove a client from the linked list
 * @details Remove a client from the linked list
 *
 * @param fd the fd of the client to remove
*/
void remove_client(const int fd)
{
    client_list_t *clients = get_clients();
    client_list_t clientNode = *clients;

    while (clientNode) {
        if (clientNode->client->fd == fd) {
            destroy_fds(clientNode->client);
            remove_from_list((node_t *)clientNode->client, (node_t *)clients);
            return;
        }
        clientNode = clientNode->next;
    }
}
