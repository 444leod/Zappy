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
 * @brief Appends a suffix to a string.
 * It there is content in the string, separates with a separator
 *
 * @param str The string to append to
 * @param suf The suffix to append
 * @param sep The potential separator
 * @return A newly allocated string
 */
static char *append_to_string(char *str, const char *suf, const char *sep)
{
    size_t strLen = strlen(str);
    size_t sufLen = strlen(suf);
    size_t sepLen = strlen(sep);
    size_t size = 1 + strLen + sufLen + (strLen > 0 ? sepLen : 0);
    char *result = malloc(size);

    result[0] = 0;
    result[size] = 0;
    strcat(result, str);
    if (strLen > 0) {
        strcat(result, sep);
        free(str);
    }
    strcat(result, suf);
    return result;
}

/**
 * @brief Format a tile content as vision list element.
 *
 * @param tile The tile
 * @return A newly allocated string
 */
static char *format_tile_content(const tile_t tile)
{
    char *str = "";

    for (uint32_t i = 0; i < get_list_size((node_t)tile->players); i++)
        str = append_to_string(str, "player", " ");
    for (uint32_t i = 0; i < tile->food; i++)
        str = append_to_string(str, "food", " ");
    for (uint32_t i = 0; i < tile->rocks.linemate; i++)
        str = append_to_string(str, "linemate", " ");
    for (uint32_t i = 0; i < tile->rocks.deraumere; i++)
        str = append_to_string(str, "deraumere", " ");
    for (uint32_t i = 0; i < tile->rocks.sibur; i++)
        str = append_to_string(str, "sibur", " ");
    for (uint32_t i = 0; i < tile->rocks.mendiane; i++)
        str = append_to_string(str, "mendiane", " ");
    for (uint32_t i = 0; i < tile->rocks.phiras; i++)
        str = append_to_string(str, "phiras", " ");
    for (uint32_t i = 0; i < tile->rocks.thystame; i++)
        str = append_to_string(str, "thystame", " ");
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
    char *str = "";
    uint32_t count = get_list_size((node_t)tiles);

    str = append_to_string(str, "[", "");
    for (uint32_t i = 0; i < count; i++) {
        suffix = format_tile_content(tiles->tile);
        str = append_to_string(str, suffix, "");
        if (i < count - 1)
            str = append_to_string(str, ", ", "");
        if (suffix[0] != 0)
            free(suffix);
        tiles = tiles->next;
    }
    return append_to_string(str, "]", "");
}

/**
 * @brief Look command
 * @details Gets the player their vision
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void look(UNUSED char **args, client_t client, server_info_t serverInfo)
{
    tile_list_t tiles = get_vision_tiles(client->player, serverInfo->map);
    const char *vision = format_vision(tiles);
    char *msg = my_strdup(vision);
    packet_t *packet = build_packet(msg);

    my_free((void *)tiles);
    free((void *)vision);
    add_packet_to_queue(&client->packetQueue, packet);
}
