/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sst
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Change the server frequency
 * @details Change the server frequency
 *
 * @param time_unit the new time unit
 * @param server_info the server info
 */
void change_server_freq(int time_unit, server_info_t server_info)
{
    char *packet_string = my_snprintf("sst %d", time_unit);
    packet_t *packet = build_packet(packet_string);

    server_info->freq = time_unit;
    queue_packet_to_client_type(GRAPHICAL, packet);
    my_free(packet_string);
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
    change_server_freq(time_unit, serverInfo);
}
