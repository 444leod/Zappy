/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_create
*/

#include "game.h"
#include "linked_lists.h"
#include "garbage_collector.h"

/**
 * @brief Create a base tile with no resources
 * @details Create a tile with no resources and no players
 *
 * @return tile_t the created tile
 */
static tile_t create_tile(void)
{
    tile_t tile = my_malloc(sizeof(struct tile_s));

    tile->players = NULL;
    tile->rocks = (rocks_t){
        .linemate = 0,
        .deraumere = 0,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0
    };
    tile->food = 0;
    return (tile);
}

/**
 * @brief Create a line with a given width
 * @details Create a line with a given width and fill it with tiles
 *
 * @param width the width of the line
 * @return line_t the created line
 */
static line_t create_line(uint32_t width)
{
    line_t line = my_malloc(sizeof(struct line_s));
    tile_list_t tile_list = NULL;
    tile_list_t tmp;
    tile_t tile = NULL;

    for (uint32_t i = 0; i < width; i++) {
        tile = create_tile();
        add_to_list((void *)tile, (node_t *)&tile_list);
    }
    tmp = (tile_list_t)get_node_by_index(get_list_size((node_t)tile_list) - 1,
        (node_t)tile_list);
    tmp->next = tile_list;
    tile_list->prev = tmp;
    line->tile_list = tile_list;
    return (line);
}

/**
 * @brief Create a map with a given width and height
 * @details Create a map with a given width and height and fill it with lines
 *
 * @param width the width of the map
 * @param height the height of the map
 * @return map_t the created map
 */
map_t create_map(uint32_t width, uint32_t height)
{
    map_t map = my_malloc(sizeof(struct map_s));
    line_t line = NULL;
    line_list_t tmp;

    for (uint32_t i = 0; i < height; i++) {
        line = create_line(width);
        add_to_list((void *)line, (node_t *)&map->line_list);
    }
    tmp = (line_list_t)get_node_by_index(
        get_list_size((node_t)map->line_list) - 1, (node_t)map->line_list);
    tmp->next = map->line_list;
    map->line_list->prev = tmp;
    map->width = width;
    map->height = height;
    return (map);
}
