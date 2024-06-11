/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** testing
*/

#pragma once

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "garbage_collector.h"
#include "server_info.h"
#include "zappy.h"

void init(void);
void assert_stdout_eq_str(char *str);
void verify_gc(gc_node_t *list, uint32_t size, ...);
server_info_t get_server_info();
client_t test_create_client(uint32_t id);
void assert_packet_queue(packet_queue_t packetQueue, uint32_t packets_number, ...);
