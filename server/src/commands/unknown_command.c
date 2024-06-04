/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** unknown_command
*/

#include "packet.h"
#include "clients.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Unknown command
 * @details Send a "ko" message to the client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server informations
 */
void unknown_command(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    char *msg = "ko";
    packet_t *packet = build_packet(msg);

    printf("Client %d: Unknown command (%s)\n", client->fd,
        get_escaped_string(args[0]));
    add_packet_to_queue(&client->packetQueue, packet);
}
