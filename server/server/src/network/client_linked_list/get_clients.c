/*
** EPITECH PROJECT, 2024
** myTeams
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
*/
client_t *get_clients(void)
{
    static client_t clients = NULL;

    return &clients;
}

/**
 * @brief Get a client by uuid
 * @details Get a client by uuid
 *
 * @param uuid the uuid of the client to get
*/
client_t get_client_by_uuid(uuid_t uuid)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    user_t current_user = NULL;

    while (tmp) {
        current_user = tmp->user;
        if (!current_user) {
            tmp = tmp->next;
            continue;
        }
        if (uuid_compare(current_user->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get all the clients logged to the given user
 * @details Get all the clients logged to the given user
 *
 * @param user the user to get the clients from
 * @param current_client the current client
 *
 * @return clients_t the clients linked list
*/
clients_t get_clients_by_user(user_t user, client_t current_client)
{
    clients_t clients = NULL;
    client_t *tmp = get_clients();
    client_t current = *tmp;

    while (current) {
        if (current == current_client) {
            current = current->next;
            continue;
        }
        if (current->user && current->user == user) {
            add_to_list((void *)current, (node_t *)&clients);
        }
        current = current->next;
    }
    return clients;
}

/**
 * @brief Get a client by fd
 * @details Get a client by fd
 *
 * @param fd the fd of the client to get
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

/**
 * @brief Get a client by username
 * @details Get a client by username
 *
 * @param username the username of the client to get
*/
client_t get_client_by_username(char *username)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    user_t current_user = NULL;

    while (tmp) {
        current_user = tmp->user;
        if (!current_user) {
            tmp = tmp->next;
            continue;
        }
        if (strcmp(current_user->username, username) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
