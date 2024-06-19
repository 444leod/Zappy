/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** select_wrapper
*/

#pragma once

#include <sys/select.h>

typedef struct select_data_s {
    fd_set *readfds;
    fd_set *writefds;
    int max_sd;
} select_data_t;
