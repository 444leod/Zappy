/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** manage_entities
*/

#include "game.h"
#include "linked_lists.h"
#include "garbage_collector.h"
#include "commands_utils.h"
#include <time.h>

/**
 * @brief Add a player to a tile at a given position
 * @details Add a player to a tile at a given position
 *
 * @param player the player to add
 * @param position the position of the tile
 * @param map the map
 */
void add_player_at_position(const player_t player, const position_t position,
    const map_t map)
{
    const tile_t tile = get_tile_at_position(position, map);

    add_to_list((void *)player, (node_t *)&(tile->players));
    player->position = position;
    player->position.x = position.x;
    player->position.y = position.y;
}

/**
 * @brief Remove a player from its tile
 * @details Remove a player from its tile
 *
 * @param player the player to remove
 * @param map the map
 */
void remove_player(const player_t player, const map_t map)
{
    const tile_t tile = get_tile_at_position(player->position, map);

    remove_from_list((void *)player, (node_t *)&tile->players);
}

/**
 * @brief Move a player to a given position
 * @details Move a player to a given position
 *
 * @param player the player
 * @param position the position
 * @param map the map
 */
void move_player(const player_t player, const position_t position,
    const map_t map)
{
    const position_t old_position = player->position;
    tile_t tile = get_tile_at_position(old_position, map);

    remove_from_list((void *)player, (node_t *)&(tile->players));
    tile = get_tile_at_position(position, map);
    add_to_list((void *)player, (node_t *)&(tile->players));
    player->position = position;
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
    const tile_t tile = get_tile_at_position(pos, map);
    const egg_t egg = my_malloc(sizeof(struct egg_s));
    static uint32_t egg_number = 0;

    egg->team = team;
    egg->pos = pos;
    egg->number = egg_number;
    egg_number++;
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
player_t egg_to_player(const egg_t egg, const map_t map)
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
    player->death_remaining_time = 0;
    clock_gettime(0, &player->last_eat_check_time);
    player->orientation = (enum ORIENTATION)(rand() % 4) + 1;
    player->egg_number = egg->number;
    tile = get_tile_at_position(egg->pos, map);
    remove_from_list((void *)egg, (node_t *)tile->eggs);
    add_to_list((void *)player, (node_t *)&tile->players);
    send_egg_player_connexion_to_graphical(egg);
    return player;
}
