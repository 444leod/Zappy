/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** debug
*/

#pragma once

#define DEBUG 0

#ifdef DEV_MODE
    #define DEBUG_PRINT(fmt, ...) debug_print(fmt, ##__VA_ARGS__)
    #define SD(c, c2, fmt, ...) debug_print_counter(c, c2, fmt, ##__VA_ARGS__)
    #define SOMETIMES_DEBUG(c, c2, fmt, ...) SD(c, c2, fmt, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
    #define SOMETIMES_DEBUG(c, c2, fmt, ...)
#endif

void debug_print(const char *fmt, ...);
void debug_print_counter(int *counter, int variation, const char *fmt, ...);
