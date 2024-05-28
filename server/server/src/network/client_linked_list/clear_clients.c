/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** clear_clients
*/

#include "clientllist.h"
#include "garbage_collector.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Clear the clients
 * @details Clear the clients linked list by closing the fds
*/
void clear_clients(void)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->fd != -1) {
            close(tmp->fd);
        }
        *clients = tmp->next;
        tmp = *clients;
    }
}
