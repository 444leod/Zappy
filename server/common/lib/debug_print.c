/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** debug_print
*/

#include <stdarg.h>
#include <stdio.h>

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
 * @brief Print a message every variation calls
 * @details Print a message every variation calls
 *
 * @param counter the counter
 * @param variation the variation
 * @param fmt the message (printf format)
 * @param ... the arguments (printf)
*/
void debug_print_counter(int *counter, int variation, const char *fmt, ...)
{
    va_list args;

    (*counter)++;
    if (*counter % variation == 0) {
        va_start(args, fmt);
        debug_print_va(fmt, args);
        va_end(args);
        (*counter) = 0;
    }
}
