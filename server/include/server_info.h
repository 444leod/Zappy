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
    uint32_t clientsNb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_list_t teams;
    map_t map;
} *server_info_t;
