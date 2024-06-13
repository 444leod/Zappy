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

void sst(char **args, const client_t client,
    const server_info_t serverInfo)
{
    int time_unit = 0;
    packet_t *packet;

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
    packet = build_packet(my_snprintf("sst %d", time_unit));
    queue_packet_to_client_type(GRAPHICAL, packet);
}
