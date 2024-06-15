/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** global_packet_send
*/

#include "packet.h"
#include "clients.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Queue a packet to all clients of a specific type
 * @details Queue a packet to all clients of a specific type
 *
 * @param type the type of the client
 * @param packet the packet to send
 */
void queue_packet_to_client_type(const enum CLIENT_TYPE type,
    packet_t *packet)
{
    client_list_t clients = get_clients_by_type(type);
    client_list_t tmp = clients;
    packet_t *packetCopy;

    while (tmp) {
        packetCopy = my_malloc(sizeof(packet_t));
        memcpy(packetCopy, packet, sizeof(packet_t));
        add_packet_to_queue(&tmp->client->packetQueue, packetCopy);
        tmp = tmp->next;
    }
}
