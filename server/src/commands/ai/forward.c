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
 * @param serverInfo the server info
 */
void forward(
    char **args,
    const client_t client,
    const server_info_t serverInfo)
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
    pos.x %= serverInfo->map->width;
    pos.y %= serverInfo->map->height;
    move_player(client->player, pos, serverInfo->map);
    add_packet_to_queue(&client->packetQueue, build_packet("ok"));
}
