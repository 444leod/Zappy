/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_users
*/

#include "clientllist.h"
#include "fcntl.h"
#include "lib.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include "debug.h"
#include "packet.h"
#include "logging_server.h"
#include "data_structures.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Check if the user had subsribed teams written in the file
 * @details Check if the user had subsribed teams written in the file
 *  by reading a char from the file
 *
 * @param fd the file descriptor
 *
 * @return true if the user had subscribed teams, false otherwise
*/
bool check_is_team_subscribed(int fd)
{
    int rd = 0;
    char is_subscribed = 0;

    rd = read(fd, &is_subscribed, sizeof(char));
    if (rd <= 0 || is_subscribed == 0)
        return false;
    return true;
}

/**
 * @brief Read a team from the save file, get its subscribed teams uuid
 * @details Read a team from the save file, get its subscribed teams uuid
 *
 * @param fd the file descriptor
 * @param user the user
 * @return true if the team was read, false otherwise
*/
bool read_team(int fd, user_t user)
{
    int rd = 0;
    team_t *team = my_malloc(sizeof(team_t));
    uuid_t team_uuid;

    rd = read(fd, team_uuid, sizeof(uuid_t));
    if (rd <= 0 || rd != sizeof(uuid_t))
        return false;
    team = get_team_by_uuid(team_uuid);
    if (!team) {
        printf("team with uuid %s not found\n", get_uuid_as_string(team_uuid));
        my_free(team);
        return true;
    }
    add_to_list((void *)team, (node_t *)&user->subscribed_teams);
    return true;
}

/**
 * @brief Add the subscribed teams to the user linked list
 * @details Add the subscribed teams to the user linked list, by reading
 *  the number written in the file, then reading the uuids of the teams
 * and adding them to the user linked list
 *
 * @param user the user
 * @param fd the file descriptor
*/
void add_subscribed_teams(user_t user, int fd)
{
    int rd = 0;
    int teams_nb = 0;

    if (!check_is_team_subscribed(fd))
        return;
    rd = read(fd, &teams_nb, sizeof(int));
    if (rd <= 0 || teams_nb <= 0)
        return;
    for (int i = 0; i < teams_nb; i++) {
        if (!read_team(fd, user))
            break;
    }
}

/**
 * @brief Read the users from the save file
 * @details Read the users from the save file
 *
 * @param fd the file descriptor
*/
void read_users(int fd)
{
    user_t new_user;
    int rd = 0;
    char *username_buffer = my_malloc(sizeof(char) * (MAX_NAME_LENGTH + 1));

    while (1) {
        new_user = my_malloc(sizeof(struct user_s));
        rd = read(fd, new_user, sizeof(struct user_s));
        if (rd <= 0 || rd != sizeof(struct user_s)) {
            my_free(new_user);
            break;
        }
        new_user->next = NULL;
        new_user->status = STATUS_NOT_LOGGED_IN;
        new_user->subscribed_teams = NULL;
        add_subscribed_teams(new_user, fd);
        add_user(new_user);
        memcpy(username_buffer, new_user->username, MAX_NAME_LENGTH + 1);
        server_event_user_loaded(
            get_uuid_as_string(new_user->uuid), username_buffer);
    }
}

/**
 * @brief Init the users linked list
 * @details Init the users linked list using the .save/.users file
*/
void init_users(void)
{
    client_t *clients = get_clients();
    int fd = open(USER_SAVE_PATH, O_RDONLY);

    *clients = NULL;
    DEBUG_PRINT("Init users\n");
    if (fd == -1) {
        printf("users: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("users: Invalid magic number\n");
        close(fd);
        return;
    }
    read_users(fd);
    close(fd);
}
