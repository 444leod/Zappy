/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** unknown_command
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"

/**
 * @brief Unknown command
 * @details Send a "ko" message to the client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void unknown_command(UNUSED char **args, client_t client,
    UNUSED server_info_t server_info)
{
    char *msg = "ko\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packet_queue, packet);
}
