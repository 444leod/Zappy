/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** change_map_ressource
*/

#include "server_info.h"
#include <string.h>

void change_map_ressource(
    const char *key, const server_info_t server_info, int8_t delta)
{
    if (strcmp(key, "food") == 0)
        server_info->actual_food += delta;
    if (strcmp(key, "linemate") == 0)
        server_info->actual_rocks.linemate += delta;
    if (strcmp(key, "deraumere") == 0)
        server_info->actual_rocks.deraumere += delta;
    if (strcmp(key, "sibur") == 0)
        server_info->actual_rocks.sibur += delta;
    if (strcmp(key, "mendiane") == 0)
        server_info->actual_rocks.mendiane += delta;
    if (strcmp(key, "phiras") == 0)
        server_info->actual_rocks.phiras += delta;
    if (strcmp(key, "thystame") == 0)
        server_info->actual_rocks.thystame += delta;
}
