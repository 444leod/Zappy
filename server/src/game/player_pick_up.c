/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_pick_up
*/

#include <string.h>
#include "game.h"

/**
 * @brief Picks up food
 */
static bool pick_food(player_t player, tile_t tile)
{
    if (tile->food == 0)
        return false;
    player->food++;
    tile->food--;
    return true;
}

/**
 * @brief Picks up linemate
 */
static bool pick_linemate(player_t player, tile_t tile)
{
    if (tile->rocks.linemate == 0)
        return false;
    player->rocks.linemate++;
    tile->rocks.linemate--;
    return true;
}

/**
 * @brief Picks up deraumere
 */
static bool pick_deraumere(player_t player, tile_t tile)
{
    if (tile->rocks.deraumere == 0)
        return false;
    player->rocks.deraumere++;
    tile->rocks.deraumere--;
    return true;
}

/**
 * @brief Picks up sibur
 */
static bool pick_sibur(player_t player, tile_t tile)
{
    if (tile->rocks.sibur == 0)
        return false;
    player->rocks.sibur++;
    tile->rocks.sibur--;
    return true;
}

/**
 * @brief Picks up mendiane
 */
static bool pick_mendiane(player_t player, tile_t tile)
{
    if (tile->rocks.mendiane == 0)
        return false;
    player->rocks.mendiane++;
    tile->rocks.mendiane--;
    return true;
}

/**
 * @brief Picks up phiras
 */
static bool pick_phiras(player_t player, tile_t tile)
{
    if (tile->rocks.phiras == 0)
        return false;
    player->rocks.phiras++;
    tile->rocks.phiras--;
    return true;
}

/**
 * @brief Picks up thystame
 */
static bool pick_thystame(player_t player, tile_t tile)
{
    if (tile->rocks.thystame == 0)
        return false;
    player->rocks.thystame++;
    tile->rocks.thystame--;
    return true;
}

/**
 * @brief Let a player pick up an item from a tile.
 * @param key the name of the content to pick up
 * @param player the player
 * @param tile the tile
 * @return `true` if it succeeded in picking up. `false` otherwise.
 */
bool player_pick_up(const char *key, player_t player, tile_t tile)
{
    pickup_command_t cmds[] = { {"food", &pick_food},
        {"linemate", &pick_linemate}, {"deraumere", &pick_deraumere},
        {"sibur", &pick_sibur}, {"mendiane", &pick_mendiane},
        {"phiras", &pick_phiras}, {"thystame", &pick_thystame},
    };

    for (uint8_t i = 0; i < 7; i++) {
        if (strcmp(cmds[i].key, key) == 0)
            return cmds[i].fun(player, tile);
    }
    return false;
}
