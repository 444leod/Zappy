/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** manage_entities
*/

#include "game.h"
#include "linked_lists.h"
#include "garbage_collector.h"

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
 * @param team the team of the eff
 * @param pos the position to add the egg at.
 * @param map the map
 */
void add_egg_at_position(const team_t team, const position_t pos, map_t map)
{
    tile_t tile = get_tile_at_position(pos, map);
    egg_t egg = my_malloc(sizeof(struct egg_s));

    egg->team = team;
    egg->pos = pos;
    add_to_list((void *)egg, (node_t *)&tile->eggs);
}

/**
 * @brief Removes an egg and pops a pops a new player at the same position.
 * @note The player is the same team as the egg.
 * @note The player IS PLACED
 *
 * @param egg the egg
 * @param map the map
 * @return The reference to the `player_t` structure allocated.
 */
player_t egg_to_player(egg_t egg, map_t map)
{
    tile_t tile = NULL;
    player_t player = NULL;

    if (egg == NULL || map == NULL)
        return NULL;
    player = my_malloc(sizeof(struct player_s));
    uuid_generate(player->id);
    player->food = 10;
    player->level = 1;
    player->team = egg->team;
    player->position = egg->pos;
    tile = get_tile_at_position(egg->pos, map);
    remove_from_list((void *)egg, (node_t *)tile->eggs);
    add_to_list((void *)player, (node_t *)&tile->players);
    return player;
}
