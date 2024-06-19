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
    client_list_t client_node = *clients;
    client_list_t next = NULL;

    while (client_node) {
        if (client_node->client->fd != -1) {
            close(client_node->client->fd);
        }
        next = client_node->next;
        remove_from_list((node_t *)client_node->client, (node_t *)clients);
        client_node = next;
    }
}
