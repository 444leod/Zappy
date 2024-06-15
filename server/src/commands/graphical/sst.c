/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sst
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"
#include "commands_utils.h"

/**
 * @brief Get the time unit modification string
 *
 * @param time_unit the time unit
 * @return char* the time unit modification string
 */
char *get_time_unit_modification_string(int time_unit)
{
    return my_snprintf("sst %d", time_unit);
}

/**
 * @brief Sst command
 * @details Set the frequency of the server
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void sst(char **args, const client_t client,
    const server_info_t serverInfo)
{
    int time_unit = 0;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: sst: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    time_unit = atoi(args[1]);
    if (!is_number(args[1]) || time_unit <= 0) {
        printf("Client %d: sst: argument is not a valid number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    serverInfo->freq = time_unit;
    queue_to_graphical(get_time_unit_modification_string(time_unit));
}
