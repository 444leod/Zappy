/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** bct
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the content of a tile as a string
 *
 * @param tile The tile to get the content from
 * @param position The position of the tile
 * @return char* The content of the tile as a string
 */
char *get_tile_content_string(const tile_t tile, const position_t position)
{
    char *tile_content_string = my_snprintf("bct %d %d %d %d %d %d %d %d %d",
        position.x, position.y,
        tile->food,
        tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane,
        tile->rocks.phiras, tile->rocks.thystame);

    return tile_content_string;
}

/**
 * @brief Send the content of a tile to a client via the bct command
 *
 * @param client The client to send the content to
 * @param serverInfo The server info
 * @param position The position of the tile
 */
static void send_tile_content_to_client(const client_t client,
    const server_info_t serverInfo, const position_t position)
{
    const tile_t tile = get_tile_at_position(position, serverInfo->map);
    char *packet_string = get_tile_content_string(tile, position);

    queue_buffer(client, packet_string);
    my_free(packet_string);
}

/**
 * @brief bct command
 * @details Send the content of a tile to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void bct(char **args, const client_t client,
    const server_info_t serverInfo)
{
    position_t pos;

    if (tablen((const void **)args) != 3) {
        printf("Client %d: bct: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    if (!is_number(args[1]) || !is_number(args[2])) {
        printf("Client %d: bct: argument is not a valid number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    pos = (position_t){atoi(args[1]), atoi(args[2])};
    if ((uint32_t)pos.x > serverInfo->width || pos.x < 0 ||
        (uint32_t)pos.y > serverInfo->height || pos.y < 0) {
        printf("Client %d: bct: invalid position\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_tile_content_to_client(client, serverInfo, pos);
}
