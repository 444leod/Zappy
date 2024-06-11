/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** right
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"

/**
 * @brief Right command
 * @details Turns the player to its right
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void right(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    const char *msg = "ok\n";
    packet_t *packet = build_packet(msg);

    client->player->orientation = (client->player->orientation % 4) + 1;
    add_packet_to_queue(&client->packetQueue, packet);
}
