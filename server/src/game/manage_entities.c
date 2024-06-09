/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** manage_entities
*/

#include "game.h"
#include "linked_lists.h"

/**
 * @brief Add a player to a tile at a given position
 * @details Add a player to a tile at a given position
 *
 * @param player the player to add
 * @param position the position of the tile
 * @param map the map
 */
void add_player_at_position(player_t player, position_t position, map_t map)
{
    tile_t tile = get_tile_at_position(position, map);

    add_to_list((void *)player, (node_t *)&tile->players);
}

/**
 * @brief Move a player to a given position
 * @details Move a player to a given position
 *
 * @param player the player
 * @param position the position
 * @param map the map
 */
void move_player(player_t player, position_t position, map_t map)
{
    position_t old_position = get_player_position(player, map);
    tile_t tile = get_tile_at_position(old_position, map);

    remove_from_list((void *)player, (node_t *)&tile->players);
    tile = get_tile_at_position(position, map);
    add_to_list((void *)player, (node_t *)&tile->players);
}

/**
 * @brief Adds an egg at a certain position.
 *
 * @param position the position to add the egg at.
 * @param map the map
 */
void add_egg_at_position(position_t position, map_t map)
{
    tile_t tile = get_tile_at_position(position, map);
}
