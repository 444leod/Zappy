/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** mct
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Mct command
 * @details Send the map content to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void mct(char **args, const client_t client,
    const server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        return;
    }
    for (uint32_t y = 0; y < server_info->height; y++) {
        for (uint32_t x = 0; x < server_info->width; x++) {
            send_tile_content(client, server_info, (position_t){x, y});
        }
    }
}
