/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include <string.h>

#include <stdio.h>

static bool tile_contains(const char *k, tile_t tile)
{
    if (strcmp(k, "food") == 0 && tile->food > 0)
        return true;
    if (strcmp(k, "linemate") == 0 && tile->rocks.linemate > 0)
        return true;
    if (strcmp(k, "deraumere") == 0 && tile->rocks.deraumere > 0)
        return true;
    if (strcmp(k, "sibur") == 0 && tile->rocks.sibur > 0)
        return true;
    if (strcmp(k, "mendiane") == 0 && tile->rocks.mendiane > 0)
        return true;
    if (strcmp(k, "phiras") == 0 && tile->rocks.phiras > 0)
        return true;
    if (strcmp(k, "thystame") == 0 && tile->rocks.thystame > 0)
        return true;
    return false;
}

static const char *get_content_arg(char **args)
{
    uint32_t count = 0;

    if (args == NULL)
        return NULL;
    for (; args[count] != NULL; count++);
    if (count != 1)
        return NULL;
    return args[0];
}

static void throw_ko(packet_queue_t *packet_queue)
{
    add_packet_to_queue(packet_queue, build_packet("ko"));
}

/**
 * @brief Fork command
 * @details Creates an egg at player's feet
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void take(char **args, client_t client, server_info_t serverInfo)
{
    player_t player = client->player;
    tile_t tile = get_tile_at_position(player->position, serverInfo->map);
    const char *arg = get_content_arg(args);

    if (arg == NULL) {
        throw_ko(&client->packetQueue);
        return;
    }
    if (!tile_contains(arg, tile)) {
        throw_ko(&client->packetQueue);
        return;
    }
    player_pick_up(arg, player, tile);
    add_packet_to_queue(&client->packetQueue, build_packet("ok"));
}
