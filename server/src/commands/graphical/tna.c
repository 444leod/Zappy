/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tna
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Tna command
 * @details Send the team names to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void tna(char **args, const client_t client,
    const server_info_t server_info)
{
    team_list_t teams;

    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        return;
    }
    teams = server_info->teams;
    while (teams) {
        queue_buffer(client, my_snprintf("tna %s", teams->team->name));
        teams = teams->next;
    }
}
