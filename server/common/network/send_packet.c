/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** send_packet
*/

#include "packet.h"
#include "magic_number.h"
#include <unistd.h>
#include <sys/socket.h>

/**
 * @brief Send a packet
 * @details Send a packet
 *
 * @param fd the file descriptor
 * @param packet the packet
 */
void send_packet(int fd, packet_t *packet)
{
    if (fd == -1)
        return;
    write_magic_number(fd);
    write(fd, packet, PACKET_SIZE);
}
