/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** debug
*/

#pragma once
#include <time.h>


#define TIMER clock_t

#ifdef DEV_MODE
    #define DEBUG_PRINT(fmt, ...) debug_print(fmt, ##__VA_ARGS__)
    #define SD(c, c2, fmt, ...) debug_print_timer(c, c2, fmt, ##__VA_ARGS__)
    #define TIMED_DEBUG_PRINT(c, c2, fmt, ...) SD(c, c2, fmt, ##__VA_ARGS__)
    #define DEBUG 1
#else
    #define DEBUG_PRINT(fmt, ...)
    #define TIMED_DEBUG_PRINT(c, c2, fmt, ...)
    #define DEBUG 0
#endif

void debug_print(const char *fmt, ...);
void debug_print_timer(TIMER *timer, double elapsed, const char *fmt, ...);
