/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** left
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"

/**
 * @brief Left command
 * @details Turns the player to its left
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void left(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    const char *msg = "ok";
    packet_t *packet = build_packet(msg);

    client->player->orientation = ((client->player->orientation - 2) % 4) + 1;
    add_packet_to_queue(&client->packetQueue, packet);
}
