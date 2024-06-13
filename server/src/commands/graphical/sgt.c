/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sgt
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief SGT command
 * @details Send the time unit to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void sgt(char **args, const client_t client,
    const server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        printf("Client %d: sgt: bad argument number\n", client->fd);
        return;
    }
    queue_buffer(client, my_snprintf("sgt %d", server_info->freq));
}
