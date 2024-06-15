/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_clients
*/

#include "clients.h"
#include <string.h>
#include <uuid/uuid.h>
#include <stdio.h>

/**
 * @brief Get the clients
 * @details Get the clients linked list
 *
 * @return the clients
*/
client_list_t *get_clients(void)
{
    static client_list_t clients = NULL;

    return &clients;
}

/**
 * @brief Get the clients by type
 * @details Get the clients by type
 *
 * @param type the type of the clients to get
 *
 * @return the clients
*/
client_list_t get_clients_by_type(const enum CLIENT_TYPE type)
{
    client_list_t clients = NULL;
    client_list_t clientNode = *get_clients();

    while (clientNode) {
        if (clientNode->client->type == type)
            add_to_list((void *)clientNode->client, (node_t *)&clients);
        clientNode = clientNode->next;
    }
    return clients;
}

/**
 * @brief Get a client by fd
 * @details Get a client by fd
 *
 * @param fd the fd of the client to get
 *
 * @return the client
*/
client_t get_client_by_fd(const int fd)
{
    client_list_t clientNode = *get_clients();

    while (clientNode) {
        if (clientNode->client->fd == fd)
            return clientNode->client;
        clientNode = clientNode->next;
    }
    return NULL;
}
