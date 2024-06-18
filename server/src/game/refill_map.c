/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** refill_map
*/

#include "server_info.h"
#include "time_utils.h"
#include <stdio.h>

/**
 * @brief Refill the map with rocks and food each 10 ticks
 *
 * @param server_info The server info
 */
void refill_map(const server_info_t server_info)
{
    update_remaining_time(&server_info->refill_wait,
        &server_info->last_refill_check);
    if (server_info->refill_wait > 0)
        return;
    server_info->last_refill_check = get_actual_time();
    fill_map(server_info->map, &server_info->actual_rocks,
        &server_info->actual_foods, NULL);
    server_info->refill_wait = REFILL_TICKS / server_info->freq;
}
