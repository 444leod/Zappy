/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** global_packet_send
*/

#include "packet.h"
#include "clientllist.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Send a packet to all logged users
 * @details Send a packet to all logged users
 *
 * @param packet the packet
 * @param client the client
 */
void send_packet_to_logged_users(packet_t *packet, client_t client)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    packet_t *new_packet = my_malloc(sizeof(packet_t));

    memcpy(new_packet, packet, sizeof(packet_t));
    new_packet->is_global = true;
    while (tmp) {
        if (tmp == client) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->user && tmp->user->status == STATUS_LOGGED_IN) {
            add_packet_to_queue(&tmp->packet_queue, new_packet);
        }
        tmp = tmp->next;
    }
}

/**
 * @brief Send a packet to a client
 * @details Send a packet to a client
 *
 * @param client the client
 * @param packet the packet
 */
void send_packet_to_client(client_t client, packet_t *packet)
{
    packet_t *new_packet = my_malloc(sizeof(packet_t));

    if (!client || client->fd == -1) {
        my_free(new_packet);
        return;
    }
    memcpy(new_packet, packet, sizeof(packet_t));
    new_packet->is_global = true;
    add_packet_to_queue(&client->packet_queue, new_packet);
}

/**
 * @brief Send a packet to all clients
 * @details Send a packet to all clients
 *
 * @param clients the clients
 * @param packet the packet
 */
void send_packet_to_clients(clients_t clients, packet_t *packet)
{
    clients_t tmp = clients;

    while (tmp) {
        send_packet_to_client(tmp->client, packet);
        tmp = tmp->next;
    }
}
