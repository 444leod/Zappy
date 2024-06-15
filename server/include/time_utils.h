/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** timeval
*/

#pragma once

#include <sys/time.h>

struct timespec get_actual_time(void);
void update_remaining_time(double *remaining_time,
    struct timespec *last_update);
int timevalcmp(struct timeval *a, struct timeval *b);
struct timeval get_timeval_by_double(double waitDuration);
