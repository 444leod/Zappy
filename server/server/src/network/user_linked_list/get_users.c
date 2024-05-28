/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_users
*/

#include "clientllist.h"
#include <uuid/uuid.h>
#include <string.h>

/**
 * @brief Get the users
 * @details Get the users linked list
*/
user_t *get_users(void)
{
    static user_t users = NULL;

    return &users;
}

/**
 * @brief Get a user by uuid
 * @details Get a user by uuid
 *
 * @param uuid the uuid of the user to get
*/
user_t get_user_by_uuid(uuid_t uuid)
{
    user_t *users = get_users();
    user_t tmp = *users;

    while (tmp) {
        if (uuid_compare(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get a user by username
 * @details Get a user by username
 *
 * @param username the username of the user to get
*/
user_t get_user_by_username(char *username)
{
    user_t *users = get_users();
    user_t tmp = *users;

    while (tmp) {
        if (strcmp(tmp->username, username) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
