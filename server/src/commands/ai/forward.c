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

/**
 * @brief Forward command
 * @details Move the player forward
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void forward(UNUSED char **args, client_t client, server_info_t serverInfo)
{
    const char *msg = "ok";
    packet_t *packet = build_packet(msg);
    position_t pos = client->player->position;

    pos.y -= client->player->orientation == NORTH;
    pos.y += client->player->orientation == SOUTH;
    pos.x += client->player->orientation == EAST;
    pos.x -= client->player->orientation == WEST;
    pos.x %= serverInfo->map->width;
    pos.y %= serverInfo->map->height;
    move_player(client->player, pos, serverInfo->map);
    add_packet_to_queue(&client->packetQueue, packet);
}
