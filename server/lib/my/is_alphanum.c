/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_alphanum
*/

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Check if a string is alphanumeric
 * @details Check if a string is alphanumeric
 *
 * @param str the string to check
 *
 * @return true if the string is alphanumeric, false otherwise
 */
bool is_alphanum(const char *str)
{
    int i = 0;

    if (str == NULL)
        return false;
    for (; str[i]; i++) {
        if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z'))
            return false;
    }
    return true;
}
