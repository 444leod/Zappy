/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** left
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "lib.h"

/**
 * @brief Left command
 * @details Turns the player to its left
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void left(
    char **args,
    const client_t client,
    UNUSED const server_info_t serverInfo)
{
    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    client->player->orientation = ((client->player->orientation - 2) % 4) + 1;
    add_packet_to_queue(&client->packetQueue, build_packet("ok"));
}
