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

void forward(UNUSED char **args, client_t client,
    UNUSED server_info_t server_info)
{
    char *msg = "ok\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packet_queue, packet);
}
