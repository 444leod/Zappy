/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clear_clients
*/

#include "clients.h"
#include "garbage_collector.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Clear the clients
 * @details Clear the clients linked list by closing the fds
*/
void clear_clients(void)
{
    client_list_t *clients = get_clients();
    client_list_t clientNode = *clients;
    client_list_t next = NULL;

    while (clientNode) {
        if (clientNode->client->fd != -1) {
            close(clientNode->client->fd);
        }
        next = clientNode->next;
        remove_from_list((node_t *)clientNode->client, (node_t *)clients);
        clientNode = next;
    }
}
