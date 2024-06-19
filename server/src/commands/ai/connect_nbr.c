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
 * @param server_info the server info
 */
void connect_nbr(
    char **args,
    const client_t client,
    UNUSED const server_info_t server_info)
{
    team_t team = client->player->team;
    char *message = NULL;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    message = my_snprintf("%d", team->remaining_slots);
    add_packet_to_queue(&client->packet_queue, build_packet(message));
    my_free(message);
}
