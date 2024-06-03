/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** unknown_command
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"

void unknown_command(UNUSED char **args, client_t client,
    UNUSED server_info_t server_info)
{
    char *msg = "ko\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packet_queue, packet);
}
