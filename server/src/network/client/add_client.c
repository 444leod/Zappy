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
void add_client(const client_t new_client)
{
    add_to_list((void *)new_client, (node_t *)get_clients());
}
