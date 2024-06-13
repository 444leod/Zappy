/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** teams
*/

#pragma once

#include <stdint.h>

typedef struct team_s {
    const char *name;
    uint32_t actualNumber;
    uint32_t remainingSlots;
} *team_t;

typedef struct team_list_s {
    struct team_list_s *next;
    struct team_list_s *prev;
    team_t team;
} *team_list_t;
