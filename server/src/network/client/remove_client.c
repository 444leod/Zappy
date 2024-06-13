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
 * @param clientNode the client to remove
*/
static void update_node(client_list_t clientNode)
{
    if (clientNode->prev)
        clientNode->prev->next = clientNode->next;
    if (clientNode->next)
        clientNode->next->prev = clientNode->prev;
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

    if (clientNode && clientNode->client->fd == fd) {
        destroy_fds(clientNode->client);
        *clients = clientNode->next;
        if (clientNode->next)
            clientNode->next->prev = NULL;
        return;
    }
    while (clientNode) {
        if (clientNode->client->fd == fd) {
            destroy_fds(clientNode->client);
            update_node(clientNode);
            return;
        }
        clientNode = clientNode->next;
    }
}
