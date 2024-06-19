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

/**
 * @brief Adds teams eggs to the map in a randomly distributed way.
 * @param map The map to add teams eggs to.
 * @param teams The list of teams.
 */
static void add_eggs(const map_t map, team_list_t teams)
{
    position_t pos = { 0, 0 };
    const uint32_t size = get_list_size((node_t)teams);

    for (uint32_t i = 0; i < size; i++) {
        DEBUG_PRINT("\tPutting egg for '%s'...", teams->team->name);
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        add_egg_at_position(teams->team, pos, map);
        teams = teams->next;
        DEBUG_PRINT(" OK!\n");
    }
}

/**
 * @brief Adds thystame to the map in an randomly distributed way.
 * @param map The map to add thystame to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_thystame(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_THYSTAME - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d thystame...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.thystame++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds phiras to the map in an randomly distributed way.
 * @param map The map to add phiras to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_phiras(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_PHIRAS - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d phiras...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.phiras++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds mendiane to the map in an randomly distributed way.
 * @param map The map to add mendiane to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_mendiane(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_MENDIANE - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d mendiane...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.mendiane++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds sibur to the map in an randomly distributed way.
 * @param map The map to add sibur to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_sibur(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_SIBUR - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d sibur...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.sibur++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds deraumere to the map in an randomly distributed way.
 * @param map The map to add deraumere to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_deraumere(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_DERAUMERE - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d deraumere...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.deraumere++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds linemate to the map in an randomly distributed way.
 * @param map The map to add linemate to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_linemate(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_LINEMATE - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d linemate...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        (*current_quantity)++;
        tile->rocks.linemate++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Adds food to the map in an randomly distributed way.
 * @param map The map to add food to.
 * @param current_quantity the current quantity of the item in the map
 */
static void add_food(const map_t map, uint32_t *current_quantity)
{
    position_t pos = { 0, 0 };
    tile_t tile = NULL;
    const uint32_t map_size = map->width * map->height;
    const uint32_t amount = map_size * D_FOOD - *current_quantity;

    DEBUG_PRINT("\tPutting in: %d food...", amount);
    for (uint32_t i = 0; i < amount; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        tile = get_tile_at_position(pos, map);
        tile->food++;
        (*current_quantity)++;
    }
    DEBUG_PRINT(" OK!\n");
}

/**
 * @brief Sets up the map, puts all the ressources on the tiles.
 * @param map The map structure to setup.
 * @param current_rocks the current rocks present in the map (ptr)
 * @param current_food the current food number present in the map (ptr)
 * @param teams the teams in the game. (NULL if no eggs to add)
 *
 * @note Ressource are density based (always the same amount for a same size).
 * @note Ressources are scarsed randomly on the map.
 */
void fill_map(const map_t map, rocks_t *current_rocks,
    uint32_t *current_food, const team_list_t teams)
{
    if (teams) {
        DEBUG_PRINT("\nMap setup:\n");
        add_eggs(map, teams);
    }
    add_food(map, current_food);
    add_linemate(map, &current_rocks->linemate);
    add_deraumere(map, &current_rocks->deraumere);
    add_sibur(map, &current_rocks->sibur);
    add_mendiane(map, &current_rocks->mendiane);
    add_phiras(map, &current_rocks->phiras);
    add_thystame(map, &current_rocks->thystame);
}
