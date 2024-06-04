/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server_info
*/

#pragma once

#include <stdint.h>

typedef struct team_name_s {
    struct team_name_s *next;
    char *name;
} *team_name_t;

typedef struct server_info_s {
    uint16_t port;
    uint32_t clientsNb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_name_t teamNames;
} *server_info_t;
