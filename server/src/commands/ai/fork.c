/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"

/**
 * @brief Fork command
 * @details Creates an egg at player's feet
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void fork_player(char **args, client_t client, server_info_t serverInfo)
{
    if (!assert_argv_count(args, 0)) {
        throw_ko(client);
        return;
    }
    add_egg_at_position(
        client->player->team,
        client->player->position,
        serverInfo->map
    );
    client->player->team->remainingSlots++;
    add_packet_to_queue(&client->packetQueue, build_packet("ok"));
}
