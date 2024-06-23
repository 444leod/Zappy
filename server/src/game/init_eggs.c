/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_eggs
*/

#include "game.h"
#include "linked_lists.h"
#include <stdlib.h>

/**
 * @brief Create eggs for a certain amount of team and a certain
 * amount of eggs per team.
 * @note These eggs have no team and count as any team
 * @param map The map to add eggs into
 * @param teams The list of teams
 * @param egg_count How many eggs per teams
 */
void init_eggs(map_t map, const team_list_t teams, uint32_t egg_count)
{
    position_t pos = {0, 0};
    uint32_t team_count = get_list_size((node_t)teams);

    for (uint32_t i = 0; i < team_count * egg_count; i++) {
        pos.x = rand() % map->width;
        pos.y = rand() % map->height;
        add_egg_at_position(NULL, pos, map);
    }
}
