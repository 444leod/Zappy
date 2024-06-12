/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connect_nbr
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"

/**
 * @brief Connect_nbr command
 * @details Tells the amount of unused slots
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void connect_nbr(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    packet_t *packet = NULL;

    packet = (client->player != NULL && client->player->team != NULL)
        ? build_packet(my_snprintf("%d", client->player->team->remainingSlots))
        : build_packet("ko");
    add_packet_to_queue(&client->packetQueue, packet);
}
