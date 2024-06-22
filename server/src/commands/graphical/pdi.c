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
 * @details Get the player death string
 *
 * @param player the player that died
 * @return char* the player death string
 */
char *get_player_death_string(const player_t player)
{
    char *player_death_str = my_snprintf("pdi %d", player->player_number);

    return player_death_str;
}
