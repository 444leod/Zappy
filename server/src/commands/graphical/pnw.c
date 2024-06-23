/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pnw
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the new player string
 *
 * @param player the player
 * @return char* the new player string
 */
char *get_new_player_string(const player_t player)
{
    char orientation = get_char_by_orientation(player->orientation);

    return my_snprintf("pnw %d %d %d %c %d %s",
        player->player_number, player->position.x, player->position.y,
        orientation, player->level, player->team->name);
}
