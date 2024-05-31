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
#include "clientllist.h"
#include "packet.h"

/**
 * @brief Send all packets queued of a client to the client
 * @details Send all packets queued of a client to the client
 *
 * @param client the client to send the packets to
 */
void send_packets(client_t client)
{
    packet_t *packet = pop_packet_from_queue(&client->packet_queue);
    int socketFd = client->fd;

    send_packet(socketFd, packet);
}
