/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_utils
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdarg.h>
#include "server_info.h"
#include "lib.h"
#include "zappy.h"
#include "packet.h"

void assert_packet_queue(packet_queue_t packetQueue, uint32_t packets_number, ...)
{
    va_list args;

    va_start(args, packets_number);
    for (uint32_t i = 0; i < packets_number; i++) {
        cr_assert_not_null(packetQueue);
        cr_assert_not_null(packetQueue->packet);
        cr_assert_not_null(packetQueue->packet->buffer);
        cr_assert_str_eq(packetQueue->packet->buffer, va_arg(args, char *));
        packetQueue = packetQueue->next;
    }
    va_end(args);
    cr_assert_null(packetQueue);
}

server_info_t get_server_info()
{
    return init_server_info((const char *[]){"./zappy_server", "-p", "4242", "-f", "1", "-c", "10", "-x", "10", "-y", "10", "-n", "teamName", "team2", NULL});
}

client_t test_create_client(uint32_t id)
{
    client_t client = create_client(id);

    client->packetQueue = NULL;
    return client;
}
