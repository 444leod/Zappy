/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** debug_print
*/

#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

/**
 * @brief Print a debug message
 * @details Print a debug message
 *
 * @param fmt the message (printf format)
 * @param ... the arguments (printf)
*/
void debug_print(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

/**
 * @brief Print a message based on variadic arguments
 *
 * @param fmt the message (printf format)
 * @param args the arguments (printf)
*/
static void debug_print_va(const char *fmt, va_list args)
{
    vfprintf(stderr, fmt, args);
}

/**
 * @brief Print a message every elapsed seconds
 * @details Print a message every elapsed seconds
 *
 * @param timer the timer
 * @param elapsed the elapsed seconds needed to print the message
 * @param fmt the message (printf format)
 * @param ... the arguments (printf)
*/
void debug_print_timer(TIMER *timer, const double elapsed,
    const char *fmt, ...)
{
    va_list args;
    const TIMER now = clock();
    double cpu_time;

    if (*timer == -1) {
        *timer = clock();
        va_start(args, fmt);
        debug_print_va(fmt, args);
        va_end(args);
        return;
    }
    cpu_time = ((double) (now - *timer)) / CLOCKS_PER_SEC * 10;
    if (cpu_time > elapsed) {
        va_start(args, fmt);
        debug_print_va(fmt, args);
        va_end(args);
        *timer = now;
    }
}
