/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_ressource_id
*/

#include "game.h"
#include <string.h>

/**
 * @brief Tries to get the id of a given ressource.
 * @param ressource The name of the ressource
 * @return The id, or -1 on fail
 */
int8_t get_ressource_id(const char *ressource)
{
    char *names[] = { "food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame", NULL };

    for (int8_t i = 0; names[i]; i++) {
        if (strcmp(names[i], ressource) == 0)
            return i;
    }
    return -1;
}
