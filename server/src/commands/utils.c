/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#include "commands.h"
#include "zappy.h"
#include "lib.h"

/**
 * @brief Send the content of a tile to a client via the bct command
 *
 * @param client The client to send the content to
 * @param serverInfo The server info
 * @param position The position of the tile
 */
void send_tile_content(const client_t client,
    const server_info_t serverInfo, const position_t position)
{
    const tile_t tile = get_tile_at_position(position, serverInfo->map);

    queue_buffer(client, my_snprintf("bct %d %d %d %d %d %d %d %d %d",
        position.x, position.y,
        tile->food,
        tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane,
        tile->rocks.phiras, tile->rocks.thystame));
}
