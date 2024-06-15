/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_number
*/

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Check if a string is a number
 * @details Check if a string is a number
 *
 * @param str the string to check
 *
 * @return true if the string is a number, false otherwise
 */
bool is_number(const char *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return false;
    if (str[0] == '-' || str[0] == '+')
        i++;
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
