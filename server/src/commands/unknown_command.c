/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** unknown_command
*/

#include "packet.h"
#include "clients.h"
#include "lib.h"
#include "zappy.h"
#include <stdio.h>

/**
 * @brief Unknown command
 * @details Send a "ko" message to the client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server informations
 */
void unknown_command(UNUSED char **args, client_t client,
    UNUSED server_info_t server_info)
{
    char *escaped_string;

    if (tablen((const void **)args) == 0)
        escaped_string = my_strdup("(null)");
    else
        escaped_string = get_escaped_string(args[0]);
    printf("Client %d: Unknown command (%s)\n", client->fd,
        escaped_string);
    my_free(escaped_string);
    if (client->type == GRAPHICAL)
        queue_buffer(client, "suc");
    else
        queue_buffer(client, "ko");
}
