/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server_info
*/

#pragma once

#include "teams.h"
#include "game.h"
#include <stdint.h>

typedef struct server_info_s {
    uint16_t port;
    uint32_t clients_nb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_list_t teams;
    map_t map;
    struct timespec last_refill_check;
    double refill_wait;
    rocks_t actual_rocks;
    uint32_t actual_foods;
} *server_info_t;
