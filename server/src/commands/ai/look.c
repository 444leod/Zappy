/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Transforms a vision coordinate into a `position_t`.
 *
 * @param player The player that is looking
 * @param depth The depth of the tile (max: level)
 * @param offset The offset of the tile [-depth; +depth]
 * @return A `position_t`
 */
static position_t get_vision_pos(player_t player, int depth, int offset)
{
    position_t pos = player->position;

    switch (player->orientation) {
        case NORTH:
            pos.x += offset;
            pos.y -= depth;
            break;
        case SOUTH:
            pos.x -= offset;
            pos.y += depth;
            break;
        case EAST:
            pos.x += depth;
            pos.y += offset;
            break;
        case WEST:
            pos.x -= depth;
            pos.y -= offset;
    }
    return pos;
}

/**
 * @brief Gets the list of tiles a player is able to see.
 *
 * @param player the player
 * @param map the map
 * @return A `tile_list_t` with tiles.
 */
static tile_list_t get_vision_tiles(const player_t player, const map_t map)
{
    tile_t tile = NULL;
    tile_list_t list = NULL;

    for (int d = 0; d <= player->level; d++) {
        for (int off = -d; off <= d; off++) {
            tile = get_tile_at_position(get_vision_pos(player, d, off), map);
            add_to_list((void *)tile, (node_t *)&list);
        }
    }
    return list;
}

/**
 * @brief Replaces a string with a new one.
 * @note Frees old.
 *
 * @param old A pointer to the old string
 * @param new The new string
 * @return A pointer to the modified old string
 */
static char *replace(char **old, char *new)
{
    my_free(*old);
    *old = new;
    return *old;
}

/**
 * @brief Format a tile content as vision list element.
 *
 * @param tile The tile
 * @return A newly allocated string
 */
static char *format_tile_content(const tile_t tile)
{
    char *str = my_strdup("");

    for (uint32_t i = 0; i < get_list_size((node_t)tile->players); i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "player"));
    for (uint32_t i = 0; i < tile->food; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "food"));
    for (uint32_t i = 0; i < tile->rocks.linemate; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "linemate"));
    for (uint32_t i = 0; i < tile->rocks.deraumere; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "deraumere"));
    for (uint32_t i = 0; i < tile->rocks.sibur; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "sibur"));
    for (uint32_t i = 0; i < tile->rocks.mendiane; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "mendiane"));
    for (uint32_t i = 0; i < tile->rocks.phiras; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "phiras"));
    for (uint32_t i = 0; i < tile->rocks.thystame; i++)
        replace(&str, supercat(3, str, (!*str ? "" : " "), "thystame"));
    return str;
}

/**
 * @brief Takes a list of tiles and format their content as vision string
 *
 * @param tiles The list of tiles
 * @return A newly allocated string to free.
 */
static char *format_vision(tile_list_t tiles)
{
    char *suffix = NULL;
    char *str = my_strdup("[");
    uint32_t count = get_list_size((node_t)tiles);

    for (uint32_t i = 0; i < count; i++) {
        suffix = format_tile_content(tiles->tile);
        replace(&str, supercat(2, str, suffix));
        my_free(suffix);
        if (i < count - 1)
            replace(&str, supercat(2, str, ","));
        tiles = tiles->next;
    }
    return replace(&str, supercat(2, str, "]"));
}

/**
 * @brief Frees all the nodes of a list without freeing the content.
 * @param list The list
 */
static void free_list_holders(node_t list)
{
    node_t next = NULL;
    node_t node = list;
    uint32_t size = get_list_size(list);

    for (uint32_t i = 0; i < size; i++) {
        next = node->next;
        my_free(node);
        node = next;
    }
}

/**
 * @brief Look command
 * @details Gets the player their vision
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void look(
    char **args,
    const client_t client,
    const server_info_t serverInfo)
{
    tile_list_t tiles = NULL;
    char *vision = NULL;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    tiles = get_vision_tiles(client->player, serverInfo->map);
    vision = format_vision(tiles);
    add_packet_to_queue(&client->packetQueue, build_packet(vision));
    my_free(vision);
    free_list_holders((node_t)tiles);
}
