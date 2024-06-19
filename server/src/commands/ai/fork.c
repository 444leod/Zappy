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
void fork_player(
    char **args,
    const client_t client,
    const server_info_t serverInfo)
{
    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    add_egg_at_position(
        client->player->team,
        client->player->position,
        serverInfo->map
    );
    client->player->team->remaining_slots++;
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
}
