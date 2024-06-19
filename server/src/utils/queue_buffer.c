/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** queue_buffer
*/

#include "clients.h"
#include "packet.h"

/**
 * @brief Queue a buffer
 * @details Queue a buffer to the client packet queue
 *
 * @param client the client
 * @param buffer the buffer to queue
 */
void queue_buffer(const client_t client, const char *buffer)
{
    add_packet_to_queue(&client->packet_queue, build_packet(buffer));
}
