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
void connect_nbr(
    char **args,
    const client_t client,
    UNUSED const server_info_t serverInfo)
{
    team_t team = client->player->team;
    char *message = NULL;

    if (!assert_argv_count(args, 0)) {
        throw_ko(client);
        return;
    }
    message = my_snprintf("%d", team->remainingSlots);
    add_packet_to_queue(&client->packetQueue, build_packet(message));
    my_free(message);
}
