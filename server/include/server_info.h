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
#include <stdbool.h>

typedef struct server_info_s {
    uint16_t port;
    uint32_t clientsNb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_list_t teams;
    map_t map;
    uint32_t remaining_eggs;
    bool end;
} *server_info_t;
