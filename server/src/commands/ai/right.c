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
void right(char **args, client_t client, UNUSED server_info_t serverInfo)
{
    if (!assert_argv_count(args, 0)) {
        throw_ko(client);
        return;
    }
    client->player->orientation = (client->player->orientation % 4) + 1;
    add_packet_to_queue(&client->packetQueue, build_packet("ok"));
}
