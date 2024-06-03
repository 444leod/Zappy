/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** params
*/

#pragma once

#include "linked_lists.h"

typedef struct param_informations_s {
    char *content;
    bool handled;
} *param_informations_t;

typedef struct param_s {
    struct param_s *next;
    param_informations_t informations;
} *param_t;

param_t get_param(char *flag, param_t params);
