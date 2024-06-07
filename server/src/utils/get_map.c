/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_to_list
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

/**
 * @brief Add a player to a tile at a given position
 * @details Add a player to a tile at a given position
 *
 * @param player the player to add
 * @param position the position of the tile
 * @param map the map
 */
void add_player_at_position(player_t *player, position_t position, map_t map)
{
    tile_t tile = get_tile_at_position(position, map);

    add_to_list((void *)player, (node_t *)&tile->players);
}

/**
 * @brief Get the position of a player in a map
 * @details Get the position of a player in a map
 *
 * @param player the player
 * @param map the map
 * @return position_t the position of the player
 */
static int get_player_in_tile_list(player_t *player, tile_list_t tile_list)
{
    int index = 1;
    tile_list_t tmp = tile_list;

    if (!tile_list)
        return (-1);
    if (get_node_index((void *)player, (node_t)tile_list->tile->players) != -1)
        return 0;
    tmp = tile_list->next;
    while (tmp != tile_list) {
        if (get_node_index((void *)player, (node_t)tmp->tile->players) != -1)
            return index;
        tmp = tmp->next;
        index++;
    }
    return -1;
}

/**
 * @brief Get the position of a player in a map
 * @details Get the position of a player in a map
 *
 * @param player the player
 * @param map the map
 * @return position_t the position of the player
 */
position_t get_player_position(player_t *player, map_t map)
{
    line_list_t line_list = map->line_list;
    uint32_t line_index = 0;
    int player_index;

    while (line_list && line_index < map->height) {
        player_index =
            get_player_in_tile_list(player, line_list->line->tile_list);
        if (player_index != -1)
            return (position_t){player_index, line_index};
        line_list = line_list->next;
        line_index++;
    }
    return (position_t){-1, -1};
}

/**
 * @brief Get the tile at a given position
 * @details Get the tile at a given position
 *
 * @param position the position
 * @param map the map
 * @return tile_t the tile
 */
tile_t get_tile_at_position(position_t position, map_t map)
{
    line_list_t line = (line_list_t)get_node_by_index(position.y,
        (node_t)map->line_list);
    tile_list_t tile;

    if (!line)
        return NULL;
    tile = (tile_list_t)get_node_by_index(position.x,
        (node_t)line->line->tile_list);
    if (!tile)
        return NULL;
    return tile->tile;
}

/**
 * @brief Move a player to a given position
 * @details Move a player to a given position
 *
 * @param player the player
 * @param position the position
 * @param map the map
 */
void move_player(player_t *player, position_t position, map_t map)
{
    position_t old_position = get_player_position(player, map);
    tile_t tile = get_tile_at_position(old_position, map);

    remove_from_list((void *)player, (node_t *)&tile->players);
    tile = get_tile_at_position(position, map);
    add_to_list((void *)player, (node_t *)&tile->players);
}
