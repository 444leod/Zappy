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
 * @param new_client the client to add
*/
void add_client(client_t new_client)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    if (!*clients) {
        *clients = new_client;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_client;
}
