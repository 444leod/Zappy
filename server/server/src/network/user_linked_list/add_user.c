/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** add_user
*/

#include "clientllist.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Add a user to the linked list
 * @details Add a user to the linked list
 *
 * @param new_user the user to add
*/
void add_user(user_t new_user)
{
    user_t *users = get_users();
    user_t tmp = *users;

    if (!*users) {
        *users = new_user;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_user;
}

/**
 * @brief Generate and add a user to the linked list by username
 * @details Generate a user based on a username and add it to the linked list
 *
 * @param username the username of the user to add
*/
void add_user_by_username(char *username)
{
    user_t new_user = my_malloc(sizeof(struct user_s));

    for (int i = 0; i < MAX_NAME_LENGTH + 1; i++)
        new_user->username[i] = 0;
    memcpy(new_user->username, username, strlen(username));
    uuid_generate(new_user->uuid);
    new_user->next = NULL;
    new_user->status = STATUS_NOT_LOGGED_IN;
    new_user->subscribed_teams = NULL;
    add_user(new_user);
}
