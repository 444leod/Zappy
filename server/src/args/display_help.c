/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_help
*/

#include "zappy.h"
#include <stdio.h>

/**
 * @brief Display the help message
 * @details Display the help message
 *
 * @param str the string to display before (optional)
 */
void display_help(char *str)
{
    if (str)
        dprintf(2, "%s\n", str);
    dprintf(2, "./zappy_server -p port -x width "
        "-y height -n name1 name2 ... -c clientsNb -f freq\n");
    my_exit(84);
}
