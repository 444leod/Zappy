/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_teams
*/

#include "data_structures.h"
#include "clientllist.h"
#include <string.h>

/**
 * @brief Get the team by uuid
 * @details Get the team by uuid
 *
 * @param team_uuid the team uuid
 *
 * @return team_t* the team
 */
team_t *get_team_by_uuid(uuid_t team_uuid)
{
    teams_t *teams = get_teams();
    teams_t tmp = *teams;

    while (tmp) {
        if (uuid_compare(tmp->team->uuid, team_uuid) == 0)
            return tmp->team;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get the team by name
 * @details Get the team by name
 *
 * @param name the name
 *
 * @return team_t* the team
 */
team_t *get_team_by_name(char *name)
{
    teams_t *teams = get_teams();
    teams_t tmp = *teams;

    while (tmp) {
        if (strcmp(tmp->team->name, name) == 0)
            return tmp->team;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get the team subscribers
 * @details Get the team subscribers
 *
 * @param team the team
 *
 * @return users_t the subscribers
 */
users_t get_team_subscribers(team_t *team)
{
    users_t subscribers = NULL;
    user_t *users = get_users();
    user_t tmp = (users ? *users : NULL);
    user_information_t *user_info;

    while (tmp) {
        if (is_user_subscribed_to_team(tmp, team->uuid)) {
            user_info = malloc(sizeof(user_information_t));
            memcpy(user_info->user_uuid, tmp->uuid, sizeof(uuid_t));
            memcpy(user_info->username, tmp->username, strlen(tmp->username));
            user_info->is_logged = tmp->status;
            add_to_list((void *)user_info, (node_t *)&subscribers);
        }
        tmp = tmp->next;
    }
    return subscribers;
}
