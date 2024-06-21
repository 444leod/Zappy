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

static position_t get_position_offset(
    enum ORIENTATION orientation)
{
    position_t pos = {0, 0};

    switch (orientation) {
        case NORTH:
            pos.y = -1;
            break;
        case EAST:
            pos.x = 1;
            break;
        case SOUTH:
            pos.y = 1;
            break;
        case WEST:
            pos.x = -1;
            break;
    }
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
void forward(UNUSED char **args, client_t client,
    UNUSED server_info_t server_info)
{
    const char *msg = "ok\n";
    packet_t *packet = build_packet(msg);
    position_t pos = get_position_offset(client->player->orientation);

    add_packet_to_queue(&client->packet_queue, packet);
    pos = (position_t){client->player->position.x + pos.x,
        client->player->position.y + pos.y};
    move_player(client->player, pos, server_info->map);
}
