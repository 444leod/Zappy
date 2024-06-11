/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** msz
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Msz command
 * @details Get the size of the map
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void msz(char **args, client_t client,
    server_info_t serverInfo)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "ko");
        return;
    }
    queue_buffer(client,
        my_snprintf("msz %d %d", serverInfo->width, serverInfo->height));
}
