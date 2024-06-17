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
    team_t team = client->player->team;
    char *message = my_snprintf("%d", team->remainingSlots);
    packet_t *packet = build_packet(message);

    my_free(message);
    add_packet_to_queue(&client->packetQueue, packet);
}
