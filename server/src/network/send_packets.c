/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** reply_code
*/

#include "fcntl.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "clients.h"
#include "packet.h"
#include "lib.h"

/**
 * @brief Send all packets queued of a client to the client
 * @details Send all packets queued of a client to the client
 *
 * @param client the client to send the packets to
 */
void send_packets(client_t client)
{
    packet_t *packet = pop_packet_from_queue(&client->packet_queue);
    const int socketFd = client->fd;

    if (packet->buffer[strlen(packet->buffer) - 1] != '\n')
        packet->buffer = supercat(2, packet->buffer, "\n");
    send_packet(socketFd, packet);
}
