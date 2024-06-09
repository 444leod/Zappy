/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_query
*/

#include "game.h"
#include "linked_lists.h"

/**
 * @brief Get the tile at a given position
 * @details Get the tile at a given position
 *
 * @param position the position
 * @param map the map
 * @return tile_t the tile
 */
tile_t get_tile_at_position(position_t position, map_t map)
{
    line_list_t line = (line_list_t)get_node_by_index(position.y,
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
static int get_player_in_tile_list(player_t player, tile_list_t tile_list)
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
position_t get_player_position(player_t player, map_t map)
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
 * @brief Gets a random egg of a certain team.
 * @details Picks the first egg found of a certain team.
 *
 * @param team the team of the egg to get
 * @param map the map
 * @return A corresponding `egg_t`, or `NULL` if not found.
 */
egg_t get_random_egg(team_t team, map_t map)
{
    return NULL;
}
