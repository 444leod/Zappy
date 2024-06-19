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
    pos.x %= server_info->map->width;
    pos.y %= server_info->map->height;
    move_player(client->player, pos, server_info->map);
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
}
