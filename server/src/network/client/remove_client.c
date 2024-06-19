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
 * @brief Update the client linked list on remove
 * @details Update the client linked list on remove
 *
 * @param client_node the client to remove
*/
static void update_node(client_list_t client_node)
{
    if (client_node->prev)
        client_node->prev->next = client_node->next;
    if (client_node->next)
        client_node->next->prev = client_node->prev;
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
    client_list_t client_node = *clients;

    if (client_node && client_node->client->fd == fd) {
        destroy_fds(client_node->client);
        *clients = client_node->next;
        if (client_node->next)
            client_node->next->prev = NULL;
        return;
    }
    while (client_node) {
        if (client_node->client->fd == fd) {
            destroy_fds(client_node->client);
            update_node(client_node);
            return;
        }
        client_node = client_node->next;
    }
}
