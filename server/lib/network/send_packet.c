/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send_packet
*/

#include "packet.h"
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

/**
 * @brief Send a packet
 * @details Send a packet
 *
 * @param fd the file descriptor
 * @param packet the packet
 */
void send_packet(const int fd, const packet_t *packet)
{
    if (fd == -1)
        return;
    write(fd, packet->buffer, strlen(packet->buffer));
}
