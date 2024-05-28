/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_teams
*/

#include "data_structures.h"

/**
 * @brief Get the teams
 * @details Get the teams
 *
 * @return teams_t* the teams
 */
teams_t *get_teams(void)
{
    static teams_t teams = NULL;

    return &teams;
}
