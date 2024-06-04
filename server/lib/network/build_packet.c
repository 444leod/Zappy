/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** build_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include "lib.h"
#include <unistd.h>
#include <string.h>

/**
 * @brief Build a packet
 * @details Build a packet with the given buffer
 *
 * @param buffer the buffer
 *
 * @return the created packet
 */
packet_t *build_packet(const char *buffer)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->buffer = my_strdup(buffer);
    return packet;
}
