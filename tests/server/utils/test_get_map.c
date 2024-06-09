/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_map
*/

#include "testing.h"
#include "game.h"
#include "linked_lists.h"
#include "garbage_collector.h"

void verify_db_linked_list_size(node_t list, uint32_t size)
{
    uint32_t i = 0;

    for (node_t tmp = list; tmp->next != list; tmp = tmp->next) {
        i++;
    }
    cr_assert_eq(i + 1, size);
}

Test(get_map, map_creation)
{
    map_t map = create_map(10, 10);

    cr_assert_not_null(map);
    verify_db_linked_list_size((node_t)map->line_list, 10);
    line_list_t line = map->line_list;
    for (uint32_t i = 0; i < 10; i++) {
        cr_assert_not_null(line);
        verify_db_linked_list_size((node_t)line->line->tile_list, 10);
        cr_assert_eq(line, line->prev->next);
        line = line->next;
    }
    cr_assert_eq(line, map->line_list);
    cr_assert_eq(map->height, 10);
    cr_assert_eq(map->width, 10);
}

Test(get_map, get_tile_at_position)
{
    map_t map = create_map(10, 10);
    tile_t tile = get_tile_at_position((position_t){0, 0}, map);

    cr_assert_not_null(tile);
    cr_assert_eq(tile->rocks.linemate, 0);
    cr_assert_eq(tile->rocks.deraumere, 0);
    cr_assert_eq(tile->rocks.sibur, 0);
    cr_assert_eq(tile->rocks.mendiane, 0);
    cr_assert_eq(tile->rocks.phiras, 0);
    cr_assert_eq(tile->rocks.thystame, 0);
    cr_assert_eq(tile->food, 0);
    cr_assert_null(tile->players);
    tile = get_tile_at_position((position_t){9, 9}, map);
    cr_assert_not_null(tile);
    cr_assert_eq(tile->rocks.linemate, 0);
    cr_assert_eq(tile->rocks.deraumere, 0);
    cr_assert_eq(tile->rocks.sibur, 0);
    cr_assert_eq(tile->rocks.mendiane, 0);
    cr_assert_eq(tile->rocks.phiras, 0);
    cr_assert_eq(tile->rocks.thystame, 0);
    cr_assert_eq(tile->food, 0);
    cr_assert_null(tile->players);
    tile_t other_tile = get_tile_at_position((position_t){10, 10}, map);
    tile = get_tile_at_position((position_t){0, 0}, map);
    cr_assert_eq(tile, other_tile);
}

Test(get_map, get_tile_at_position_special)
{
    map_t map = create_map(10, 10);
    map->line_list->line->tile_list->tile->food = 10;

    tile_t tile = get_tile_at_position((position_t){0, 0}, map);
    cr_assert_not_null(tile);
    cr_assert_eq(tile->food, 10);

    player_t player = my_malloc(sizeof(player_t));
    player->id = 1;
    player->team = NULL;

    add_to_list((void *)player, (node_t *)&tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);

    player = my_malloc(sizeof(player_t));
    player->id = 2;
    player->team = NULL;

    add_to_list((void *)player, (node_t *)&tile->players);
    cr_assert_eq(tile->players->player->id, 1);
    cr_assert_eq(tile->players->next->player->id, 2);
}

Test(get_map, add_player_at_position)
{
    map_t map = create_map(10, 10);
    player_t player = my_malloc(sizeof(player_t));
    player->id = 1;
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    tile_t tile = get_tile_at_position((position_t){1, 1}, map);
    cr_assert_not_null(tile);
    cr_assert_eq(tile->food, 0);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    player = my_malloc(sizeof(player_t));
    player->id = 2;
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    cr_assert_eq(tile->players->player->id, 1);
    cr_assert_eq(tile->players->next->player->id, 2);
    cr_assert_eq(get_list_size((node_t)tile->players), 2);
}

Test(get_map, get_player_position)
{
    map_t map = create_map(10, 10);
    player_t player = my_malloc(sizeof(player_t));
    player->id = 1;
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    position_t position = get_player_position(player, map);
    cr_assert_eq(position.x, 1);
    cr_assert_eq(position.y, 1);
    player = my_malloc(sizeof(player_t));
    player->id = 2;
    player->team = NULL;

    add_player_at_position(player, (position_t){2, 5}, map);
    position = get_player_position(player, map);
    cr_assert_eq(position.x, 2);
    cr_assert_eq(position.y, 5);
    player = my_malloc(sizeof(player_t));
    player->id = 3;
    player->team = NULL;

    add_player_at_position(player, (position_t){2, 5}, map);
    position = get_player_position(player, map);
    cr_assert_eq(position.x, 2);
    cr_assert_eq(position.y, 5);
}

Test(get_map, move_player)
{
    map_t map = create_map(10, 10);
    player_t player = my_malloc(sizeof(player_t));
    player->id = 1;
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    position_t position = get_player_position(player, map);
    cr_assert_eq(position.x, 1);
    cr_assert_eq(position.y, 1);
    move_player(player, (position_t){2, 2}, map);
    position = get_player_position(player, map);
    cr_assert_eq(position.x, 2);
    cr_assert_eq(position.y, 2);
    move_player(player, (position_t){2, 2}, map);
    position = get_player_position(player, map);
    cr_assert_eq(position.x, 2);
    cr_assert_eq(position.y, 2);
    move_player(player, (position_t){9, 9}, map);
    position = get_player_position(player, map);
    cr_assert_eq(position.x, 9);
    cr_assert_eq(position.y, 9);
}
