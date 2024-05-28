/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_users
*/

#include "clientllist.h"
#include <fcntl.h>
#include <unistd.h>
#include "magic_number.h"

/**
 * @brief Write the teams uuids to a file
 * @details Write the teams uuids to a file
 *
 * @param fd the file descriptor
 * @param teams the teams
 */
void write_teams_uuids(int fd, teams_t *teams)
{
    teams_t tmp = *teams;
    int nb_teams = 0;
    char is_subscribed = 1;

    if (teams == NULL || *teams == NULL)
        return;
    write(fd, &is_subscribed, sizeof(char));
    while (tmp) {
        nb_teams++;
        tmp = tmp->next;
    }
    tmp = *teams;
    write(fd, &nb_teams, sizeof(int));
    while (tmp) {
        write(fd, tmp->team->uuid, sizeof(uuid_t));
        tmp = tmp->next;
    }
}

/**
 * @brief Dump the users to a file
 * @details Dump the users to a file
 */
void dump_users(void)
{
    user_t *users = get_users();
    user_t tmp = *users;
    int fd = open(USER_SAVE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    char is_subscribed = 0;

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        tmp->status = STATUS_NOT_LOGGED_IN;
        write(fd, tmp, sizeof(struct user_s));
        if (tmp->subscribed_teams != NULL)
            write_teams_uuids(fd, &tmp->subscribed_teams);
        else
            write(fd, &is_subscribed, sizeof(char));
        tmp = tmp->next;
    }
}
