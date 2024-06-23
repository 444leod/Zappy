/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** right
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "lib.h"

/**
 * @brief Right command
 * @details Turns the player to its right
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void right(
    char **args,
    const client_t client,
    UNUSED const server_info_t server_info)
{
    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    client->player->orientation = (client->player->orientation % 4) + 1;
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
}
