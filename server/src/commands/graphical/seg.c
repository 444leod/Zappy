/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** seg
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Give the game end string based on the given team
 * @details Give the game end string based on the given team
 *  if the team is NULL, then its a tie, otherwise give "seg TEAM_NAME"
 *
 * @param team the last standing team or NULL
 *
 * @return char * the string
 */
char *get_game_end_string(team_t team)
{
    if (!team)
        return my_strdup("tie");
    else
        return my_snprintf("seg %s", team->name);
}
