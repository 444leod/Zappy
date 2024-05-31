/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_clients
*/

#include "clientllist.h"
#include <string.h>
#include <uuid/uuid.h>
#include <stdio.h>

/**
 * @brief Get the clients
 * @details Get the clients linked list
 *
 * @return the clients
*/
client_t *get_clients(void)
{
    static client_t clients = NULL;

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
clients_t get_clients_by_type(enum CLIENT_TYPE type)
{
    clients_t clients = NULL;
    client_t *tmp = get_clients();
    client_t current = *tmp;

    while (current) {
        if (current->type == type)
            add_to_list((void *)current, (node_t *)&clients);
        current = current->next;
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
client_t get_client_by_fd(int fd)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->fd == fd)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
