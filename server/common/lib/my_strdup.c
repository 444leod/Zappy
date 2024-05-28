/*
** EPITECH PROJECT, 2024
** myTeams
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
char *my_strdup(char const *src)
{
    char *dest = my_malloc(sizeof(char) * (strlen(src) + 1));

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
char *my_strndup(char const *src, int n)
{
    char *dest = my_malloc(sizeof(char) * (n + 1));

    strncpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}
