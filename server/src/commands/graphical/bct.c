/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** bct
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief bct command
 * @details Get the size of the map
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
        queue_buffer(client, "ko");
        return;
    }
    if (!is_number(args[1]) || !is_number(args[2])) {
        queue_buffer(client, "ko");
        return;
    }
    pos = (position_t){atoi(args[1]), atoi(args[2])};
    if ((uint32_t)pos.x > serverInfo->width || pos.x < 0 ||
        (uint32_t)pos.y > serverInfo->height || pos.y < 0) {
        queue_buffer(client, "ko");
        return;
    }
    send_tile_content(client, serverInfo, pos);
}
