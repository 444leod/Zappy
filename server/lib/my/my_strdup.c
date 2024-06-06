/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** my_strdup
*/

#include <stdlib.h>
#include <string.h>
#include "garbage_collector.h"

/**
 * @brief Duplicate a string
 * @details Duplicate a string
 *
 * @param src the string to duplicate
 *
 * @return the duplicated string
*/
char *my_strdup(const char *src)
{
    char *dest;

    if (src == NULL)
        return NULL;
    dest = my_malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dest, src);
    return dest;
}

/**
 * @brief Duplicate a string of n characters
 * @details Duplicate a string of n characters
 *
 * @param src the string to duplicate
 * @param n the number of characters to duplicate
 *
 * @return the duplicated string
*/
char *my_strndup(const char *src, const uint32_t n)
{
    char *dest;

    if (src == NULL)
        return NULL;
    dest = my_malloc(sizeof(char) * (n + 1));
    strncpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}
