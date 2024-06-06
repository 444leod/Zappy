/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** forward
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"

/**
 * @brief Forward command
 * @details Move the player forward
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void forward(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    const char *msg = "ok\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packetQueue, packet);
}
