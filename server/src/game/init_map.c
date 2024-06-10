/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_map
*/

#include <stdlib.h>
#include "debug.h"
#include "game.h"
#include "server_info.h"
#include "linked_lists.h"

static void add_eggs(map_t map, team_list_t teams)
{
    position_t pos = { 0, 0 };
    uint32_t size = get_list_size((node_t)teams);

    for (uint32_t i = 0; i < size; i++) {
        DEBUG_PRINT("\tPutting egg for '%s'...", teams->team->name);
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        add_egg_at_position(teams->team, pos, map);
        teams = teams->next;
        DEBUG_PRINT(" OK!\n");
    }
}

static void add_thystame(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_THYSTAME;

    DEBUG_PRINT("\tPutting in: %d thystame...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.thystame++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_phiras(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_PHIRAS;

    DEBUG_PRINT("\tPutting in: %d phiras...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.phiras++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_mendiane(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_MENDIANE;

    DEBUG_PRINT("\tPutting in: %d mendiane...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.mendiane++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_sibur(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_SIBUR;

    DEBUG_PRINT("\tPutting in: %d sibur...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.sibur++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_deraumere(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_DERAUMERE;

    DEBUG_PRINT("\tPutting in: %d deraumere...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.deraumere++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_linemate(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_LINEMATE;

    DEBUG_PRINT("\tPutting in: %d linemate...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->rocks.linemate++;
    }
    DEBUG_PRINT(" OK!\n");
}

static void add_food(map_t map)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    uint32_t amount = map->width * map->height * D_FOOD;

    DEBUG_PRINT("\tPutting in: %d food...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->food++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Sets up the map, puts all the ressources on the tiles.
 * @param map The map structure to setup.
 *
 * @note Ressource are density based (always the same amount for a same size).
 * @note Ressources are scarsed randomly on the map.
 */
void init_map(map_t map, team_list_t teams)
{
    if (map == NULL || teams == NULL)
        return;
    DEBUG_PRINT("\nMap setup:\n");
    add_food(map);
    add_linemate(map);
    add_deraumere(map);
    add_sibur(map);
    add_mendiane(map);
    add_phiras(map);
    add_thystame(map);
    add_eggs(map, teams);
}
