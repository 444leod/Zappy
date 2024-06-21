/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** forward
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"

/**
 * @brief Computes a wrapped version of a position with a given map
 * @param pos The position
 * @param map The map
 * @return a `position_t` wrapped around map borders
 */
static position_t wrap_pos(position_t pos, const map_t map)
{
    while (pos.x < 0)
        pos.x += map->width;
    while (pos.y < 0)
        pos.y += map->height;
    while (pos.x >= (int)map->width)
        pos.x -= map->width;
    while (pos.y >= (int)map->height)
        pos.y -= map->height;
    return pos;
}

/**
 * @brief Forward command
 * @details Move the player forward
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void forward(
    char **args,
    const client_t client,
    const server_info_t server_info)
{
    position_t pos = client->player->position;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    pos.y -= client->player->orientation == NORTH;
    pos.y += client->player->orientation == SOUTH;
    pos.x += client->player->orientation == EAST;
    pos.x -= client->player->orientation == WEST;
    pos = wrap_pos(pos, (const map_t)server_info->map);
    move_player(client->player, pos, server_info->map);
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
}
