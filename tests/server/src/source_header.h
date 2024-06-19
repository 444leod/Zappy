/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** source_header
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "garbage_collector.h"
#include "server_info.h"
#include "zappy.h"
#include "testing.h"

server_info_t get_server_info();
client_t test_create_client(uint32_t id);
void assert_packet_queue(packet_queue_t packet_queue, uint32_t packets_number, ...);
