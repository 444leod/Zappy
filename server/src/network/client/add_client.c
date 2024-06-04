/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_client
*/

#include "clients.h"

/**
 * @brief Add a client to the linked list
 * @details Add a client to the linked list
 *
 * @param newClient the client to add
*/
void add_client(const client_t newClient)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    if (!*clients) {
        *clients = newClient;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = newClient;
}
