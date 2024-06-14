/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_pick_up
*/

#include <string.h>
#include <stdlib.h>
#include "game.h"

/**
 * @brief Picks up food
 */
static bool pick_food(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->food < min)
        return false;
    if (delta >= 0 && tile->food < min)
        return false;
    player->food += delta;
    tile->food -= delta;
    return true;
}

/**
 * @brief Picks up linemate
 */
static bool pick_linemate(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.linemate < min)
        return false;
    if (delta >= 0 && tile->rocks.linemate < min)
        return false;
    player->rocks.linemate += delta;
    tile->rocks.linemate -= delta;
    return true;
}

/**
 * @brief Picks up deraumere
 */
static bool pick_deraumere(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.deraumere < min)
        return false;
    if (delta >= 0 && tile->rocks.deraumere < min)
        return false;
    player->rocks.deraumere += delta;
    tile->rocks.deraumere -= delta;
    return true;
}

/**
 * @brief Picks up sibur
 */
static bool pick_sibur(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.sibur < min)
        return false;
    if (delta >= 0 && tile->rocks.sibur < min)
        return false;
    player->rocks.sibur += delta;
    tile->rocks.sibur -= delta;
    return true;
}

/**
 * @brief Picks up mendiane
 */
static bool pick_mendiane(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.mendiane < min)
        return false;
    if (delta >= 0 && tile->rocks.mendiane < min)
        return false;
    player->rocks.mendiane += delta;
    tile->rocks.mendiane -= delta;
    return true;
}

/**
 * @brief Picks up phiras
 */
static bool pick_phiras(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.phiras < min)
        return false;
    if (delta >= 0 && tile->rocks.phiras < min)
        return false;
    player->rocks.phiras += delta;
    tile->rocks.phiras -= delta;
    return true;
}

/**
 * @brief Picks up thystame
 */
static bool pick_thystame(player_t player, tile_t tile, int8_t delta)
{
    uint32_t min = abs(delta);

    if (delta < 0 && player->rocks.thystame < min)
        return false;
    if (delta >= 0 && tile->rocks.thystame < min)
        return false;
    player->rocks.thystame += delta;
    tile->rocks.thystame -= delta;
    return true;
}

/**
 * @brief Transfers content from a tile to a player's inventory.
 * @param key the name of the content to pick up
 * @param player the player
 * @param tile the tile
 * @param delta `>0` to add to the player inventory.
 *  `<0` to take from player inventory
 * @return `true` if it succeeded in picking up. `false` otherwise.
 */
bool player_pick_up(
    const char *key, player_t player, tile_t tile, int8_t delta)
{
    pickup_command_t cmds[] = { {"food", &pick_food},
        {"linemate", &pick_linemate}, {"deraumere", &pick_deraumere},
        {"sibur", &pick_sibur}, {"mendiane", &pick_mendiane},
        {"phiras", &pick_phiras}, {"thystame", &pick_thystame},
    };

    for (uint8_t i = 0; i < 7; i++) {
        if (strcmp(cmds[i].key, key) == 0)
            return cmds[i].fun(player, tile, delta);
    }
    return false;
}
