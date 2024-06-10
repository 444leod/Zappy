/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_query
*/

#include <stdlib.h>
#include "game.h"
#include "linked_lists.h"
#include "garbage_collector.h"

/**
 * @brief Get the tile at a given position
 * @details Get the tile at a given position
 *
 * @param position the position
 * @param map the map
 * @return tile_t the tile
 */
tile_t get_tile_at_position(const position_t position, const map_t map)
{
    const line_list_t line = (line_list_t)get_node_by_index(position.y,
        (node_t)map->line_list);
    tile_list_t tile;

    if (!line)
        return NULL;
    tile = (tile_list_t)get_node_by_index(position.x,
        (node_t)line->line->tile_list);
    if (!tile)
        return NULL;
    return tile->tile;
}

/**
 * @brief Get the position of a player in a map
 * @details Get the position of a player in a map
 *
 * @param player the player
 * @param map the map
 * @return position_t the position of the player
 */
static int get_player_in_tile_list(const player_t player,
    const tile_list_t tile_list)
{
    int index = 1;
    tile_list_t tmp = tile_list;

    if (!tile_list)
        return (-1);
    if (get_node_index((void *)player, (node_t)tile_list->tile->players) != -1)
        return 0;
    tmp = tile_list->next;
    while (tmp != tile_list) {
        if (get_node_index((void *)player, (node_t)tmp->tile->players) != -1)
            return index;
        tmp = tmp->next;
        index++;
    }
    return -1;
}

/**
 * @brief Get the position of a player in a map
 * @details Get the position of a player in a map
 *
 * @param player the player
 * @param map the map
 * @return position_t the position of the player
 */
position_t get_player_position(const player_t player, const map_t map)
{
    line_list_t line_list = map->line_list;
    uint32_t line_index = 0;
    int player_index;

    while (line_list && line_index < map->height) {
        player_index =
            get_player_in_tile_list(player, line_list->line->tile_list);
        if (player_index != -1)
            return (position_t){player_index, line_index};
        line_list = line_list->next;
        line_index++;
    }
    return (position_t){-1, -1};
}

/**
 * @brief Adds all eggs of a tile to a list
 * @warning No real team equality check, could fail!
 *
 * @param eggs a pointer to a egg_list
 * @param tile the tile
 */
static void accumulate_tile_eggs(
    egg_list_t *eggs, const tile_t tile, const team_t team)
{
    egg_list_t list = NULL;
    uint32_t size = 0;

    if (tile == NULL || eggs == NULL)
        return;
    list = tile->eggs;
    size = get_list_size((node_t)list);
    for (uint32_t i = 0; i < size; i++) {
        if (list->egg->team == team)
            add_to_list((void *)list->egg, (node_t *)eggs);
        list = list->next;
    }
}

/**
 * @brief Gets all the eggs of a certain team
 *
 * @param team the team to get the eggs of
 * @param map the map to query into
 */
egg_list_t get_team_eggs(const team_t team, const map_t map)
{
    egg_list_t list = NULL;
    tile_t tile = NULL;

    if (team == NULL || map == NULL)
        return NULL;
    for (uint32_t y = 0; y < map->height; y++) {
        for (uint32_t x = 0; x < map->width; x++) {
            tile = get_tile_at_position((position_t){x, y}, map);
            accumulate_tile_eggs(&list, tile, team);
        }
    }
    return list;
}

/**
 * @brief Gets a random egg of a certain team.
 * @details Picks the first egg found of a certain team.
 *
 * @param team the team of the egg to get
 * @param map the map
 * @return A corresponding `egg_t`, or `NULL` if not found.
 */
egg_t get_random_egg(const team_t team, const map_t map)
{
    const egg_list_t list = get_team_eggs(team, map);
    uint32_t index = 0;
    uint32_t size = 0;
    egg_list_t node = NULL;

    if (list == NULL)
        return NULL;
    size = get_list_size((node_t)list);
    if (size == 0)
        return NULL;
    index = rand() % size;
    node = (egg_list_t)get_node_by_index(index, (node_t)list);
    return node == NULL ? NULL : node->egg;
}
