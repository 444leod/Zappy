/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdi
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the player death string
 *
 * @param player The player
 *
 * @return char* The player death string
 */
char *get_player_death_string(const player_t player)
{
    return my_snprintf("pdi %d\n", player->id);
}
