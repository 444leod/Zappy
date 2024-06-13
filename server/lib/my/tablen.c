/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tablen
*/

#include <stddef.h>

/**
 * @brief Get the length of a table
 * @details Get the length of a table
 *
 * @param tab the table
 *
 * @return the length of the table
*/
int tablen(const void **tab)
{
    int i = 0;

    if (tab == NULL)
        return (0);
    while (tab[i] != (void *)0)
        i++;
    return i;
}
