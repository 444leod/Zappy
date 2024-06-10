/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** msz
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "clients.h"

/**
 * @brief Msz command
 * @details Get the size of the map
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void msz(UNUSED char **args, client_t client,
    server_info_t serverInfo)
{
    queue_buffer(client, my_snprintf("msz %d %d\n",
        serverInfo->width, serverInfo->height));
}
