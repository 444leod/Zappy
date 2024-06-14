/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_pick_up
*/

#include <string.h>
#include "game.h"

static void player_pick_food(player_t player, tile_t tile)
{
    player->food++;
    tile->food--;
}

static void player_pick_linemate(player_t player, tile_t tile)
{
    player->rocks.linemate++;
    tile->rocks.linemate--;
}

static void player_pick_deraumere(player_t player, tile_t tile)
{
    player->rocks.deraumere++;
    tile->rocks.deraumere--;
}

static void player_pick_sibur(player_t player, tile_t tile)
{
    player->rocks.sibur++;
    tile->rocks.sibur--;
}

static void player_pick_mendiane(player_t player, tile_t tile)
{
    player->rocks.mendiane++;
    tile->rocks.mendiane--;
}

static void player_pick_phiras(player_t player, tile_t tile)
{
    player->rocks.phiras++;
    tile->rocks.phiras--;
}

static void player_pick_thystame(player_t player, tile_t tile)
{
    player->rocks.thystame++;
    tile->rocks.thystame--;
}

void player_pick_up(const char *key, player_t player, tile_t tile)
{
    if (strcmp(key, "food") == 0)
        player_pick_food(player, tile);
    if (strcmp(key, "linemate") == 0)
        player_pick_linemate(player, tile);
    if (strcmp(key, "deraumere") == 0)
        player_pick_deraumere(player, tile);
    if (strcmp(key, "sibur") == 0)
        player_pick_sibur(player, tile);
    if (strcmp(key, "mendiane") == 0)
        player_pick_mendiane(player, tile);
    if (strcmp(key, "phiras") == 0)
        player_pick_phiras(player, tile);
    if (strcmp(key, "thystame") == 0)
        player_pick_thystame(player, tile);
}
