/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server_info
*/

#pragma once

#include "teams.h"
#include <stdint.h>

typedef struct team_list_s {
    struct team_list_s *next;
    team_t team;
} *team_list_t;

typedef struct server_info_s {
    uint16_t port;
    uint32_t clientsNb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_list_t teams;
} *server_info_t;
