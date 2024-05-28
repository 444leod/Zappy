/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** is_user
*/

#include "linked_lists.h"
#include "clientllist.h"

/**
 * @brief Check if the given user is subscribed to the given team
 * @details Check if the given user is subscribed to the given team
 *
 * @param user the user
 * @param team_uuid the team uuid
 *
 * @return true if the user is subscribed to the team
 * @return false if the user is not subscribed to the team
*/
bool is_user_subscribed_to_team(user_t user, uuid_t team_uuid)
{
    teams_t tmp = user->subscribed_teams;

    while (tmp) {
        if (uuid_compare(tmp->team->uuid, team_uuid) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}
