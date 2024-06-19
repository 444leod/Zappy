/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "zappy.h"

/**
 * @brief Gets the first argument if there is one
 * @param args the argument list
 * @return NULL if it failed, the first arg if there is one.
 */
static const char *get_content_arg(char **args)
{
    uint32_t count = tablen((const void **)args);

    if (count != 2)
        return NULL;
    return args[1];
}

/**
 * @brief Take command
 * @details Let a user pick up an object from the tile it's on.
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void take(
    char **args,
    const client_t client,
    const server_info_t server_info)
{
    player_t player = client->player;
    tile_t tile = NULL;
    const char *arg = get_content_arg(args);

    if (arg == NULL) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(player->position, server_info->map);
    if (!player_pick_up(arg, player, tile, 1)) {
        throw_ko(client);
        return;
    }
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
    change_map_ressource(arg, server_info, -1);
}
