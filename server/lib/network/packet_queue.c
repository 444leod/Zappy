/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** packet_queue
*/

#include "packet.h"
#include "garbage_collector.h"

void add_packet_to_queue(packet_queue_t *queue, packet_t *packet)
{
    packet_queue_t new_packet = my_malloc(sizeof(struct packet_queue_s));
    packet_queue_t tmp;

    new_packet->packet = packet;
    new_packet->next = NULL;
    if (!*queue) {
        *queue = new_packet;
        return;
    }
    tmp = *queue;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_packet;
}

packet_t *pop_packet_from_queue(packet_queue_t *queue)
{
    packet_queue_t tmp;
    packet_t *packet;

    if (!*queue)
        return NULL;
    tmp = *queue;
    *queue = tmp->next;
    packet = tmp->packet;
    my_free(tmp);
    return packet;
}

void free_packet_queue(packet_queue_t *queue)
{
    packet_t *packet;

    packet = pop_packet_from_queue(queue);
    while (packet) {
        my_free(packet);
        packet = pop_packet_from_queue(queue);
    }
}
