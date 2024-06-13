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
 * @details Send the map size to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void msz(char **args, client_t client,
    server_info_t serverInfo)
{
    char *packet_string;

    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        return;
    }
    packet_string = my_snprintf("msz %d %d",
        serverInfo->width, serverInfo->height);
    queue_buffer(client, packet_string);
    my_free(packet_string);
}
