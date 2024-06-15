/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_map
*/

#include "source_header.h"
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
    uuid_t id1;
    uuid_generate(id1);
    uuid_copy(player->id, id1);
    player->team = NULL;

    add_to_list((void *)player, (node_t *)&tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert(uuid_compare(tile->players->player->id, player->id) == 0);

    player = my_malloc(sizeof(player_t));
    uuid_t id2;
    uuid_generate(id2);
    uuid_copy(player->id, id2);
    player->team = NULL;

    add_to_list((void *)player, (node_t *)&tile->players);
    cr_assert(uuid_compare(tile->players->player->id, id1) == 0);
    cr_assert(uuid_compare(tile->players->next->player->id, id2) == 0);
}

Test(get_map, add_player_at_position)
{
    map_t map = create_map(10, 10);
    player_t player = my_malloc(sizeof(player_t));
    uuid_t id1;
    uuid_generate(id1);
    uuid_copy(player->id, id1);
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    tile_t tile = get_tile_at_position((position_t){1, 1}, map);
    cr_assert_not_null(tile);
    cr_assert_eq(tile->food, 0);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    player = my_malloc(sizeof(player_t));
    uuid_t id2;
    uuid_generate(id2);
    uuid_copy(player->id, id2);
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    cr_assert_eq(tile->players->next->player, player);
    cr_assert(uuid_compare(tile->players->player->id, id1) == 0);
    cr_assert(uuid_compare(tile->players->next->player->id, id2) == 0);
    cr_assert_eq(get_list_size((node_t)tile->players), 2);
}

Test(get_map, move_player)
{
    map_t map = create_map(10, 10);
    player_t player = my_malloc(sizeof(player_t));
    uuid_t id1;
    uuid_generate(id1);
    uuid_copy(player->id, id1);
    player->team = NULL;

    add_player_at_position(player, (position_t){1, 1}, map);
    tile_t tile = get_tile_at_position((position_t){1, 1}, map);
    cr_assert_not_null(tile);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(player->position.x, 1);
    cr_assert_eq(player->position.y, 1);

    move_player(player, (position_t){2, 2}, map);
    cr_assert_null(tile->players);
    tile = get_tile_at_position((position_t){2, 2}, map);
    cr_assert_not_null(tile);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(player->position.x, 2);
    cr_assert_eq(player->position.y, 2);

    move_player(player, (position_t){2, 2}, map);
    tile = get_tile_at_position((position_t){2, 2}, map);
    cr_assert_not_null(tile);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(player->position.x, 2);
    cr_assert_eq(player->position.y, 2);

    move_player(player, (position_t){9, 9}, map);
    cr_assert_null(tile->players);
    tile = get_tile_at_position((position_t){9, 9}, map);
    cr_assert_not_null(tile);
    cr_assert_not_null(tile->players);
    cr_assert_eq(tile->players->player, player);
    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(player->position.x, 9);
    cr_assert_eq(player->position.y, 9);
}

Test(get_map, init_map_food)
{
    struct team_list_s teams = { 0 };
    map_t map = create_map(2, 2);
    init_map(map, &teams);

    tile_t a = get_tile_at_position((position_t){0, 0}, map);
    cr_assert(a != NULL);
    tile_t b = get_tile_at_position((position_t){0, 1}, map);
    cr_assert(b != NULL);
    tile_t c = get_tile_at_position((position_t){1, 0}, map);
    cr_assert(c != NULL);
    tile_t d = get_tile_at_position((position_t){1, 1}, map);
    cr_assert(d != NULL);

    uint32_t food = a->food + b->food + c ->food + d->food;
    cr_assert(food == 2);
}

Test(get_map, init_map_rocks)
{
    struct team_list_s teams = { 0 };
    map_t map = create_map(5, 5);
    rocks_t rocks = { 0 };
    init_map(map, &teams);

    line_list_t line = map->line_list;
    for (int y = 0; y < 5; y++) {
        tile_list_t tile = line->line->tile_list;
        for (int x = 0; x < 5; x++) {
            rocks.linemate += tile->tile->rocks.linemate;
            rocks.deraumere += tile->tile->rocks.deraumere;
            rocks.sibur += tile->tile->rocks.sibur;
            rocks.mendiane += tile->tile->rocks.mendiane;
            rocks.phiras += tile->tile->rocks.phiras;
            rocks.thystame += tile->tile->rocks.thystame;
            tile = tile->next;
        }
        line = line->next;
    }
    cr_assert(rocks.linemate == 7);
    cr_assert(rocks.deraumere == 3);
    cr_assert(rocks.sibur == 2);
    cr_assert(rocks.mendiane == 2);
    cr_assert(rocks.phiras == 2);
    cr_assert(rocks.thystame == 1);
}

Test(get_map, init_map_eggs)
{
    team_list_t teams = NULL;
    struct team_s teamA = { "Good guys", 0, 1 };
    struct team_s teamB = { "Mean guys", 0, 1 };
    struct team_s teamC = { "Unknowns", 0, 1 };
    add_to_list((void *)&teamA, (node_t *)&teams);
    add_to_list((void *)&teamB, (node_t *)&teams);
    map_t map = create_map(5, 5);
    init_map(map, teams);
    uint32_t a = get_list_size((node_t)get_team_eggs(&teamA, map));
    uint32_t b = get_list_size((node_t)get_team_eggs(&teamB, map));
    uint32_t c = get_list_size((node_t)get_team_eggs(&teamC, map));
    cr_assert(a == 1);
    cr_assert(b == 1);
    cr_assert(c == 0);
}

Test(get_map, adding_eggs)
{
    position_t pos = {0, 0};
    map_t map = create_map(1, 1);
    tile_t tile = get_tile_at_position(pos, map);
    struct team_s team = {
        .name = "Example Team",
        .actualNumber = 0,
        .remainingSlots = 1
    };
    uint32_t eggCount = 0;

    eggCount = get_list_size((node_t)tile->eggs);
    cr_assert(eggCount == 0);

    add_egg_at_position(&team, pos, map);
    add_egg_at_position(&team, pos, map);
    add_egg_at_position(&team, pos, map);
    add_egg_at_position(&team, pos, map);

    eggCount = get_list_size((node_t)tile->eggs);
    cr_assert(eggCount == 4);
    cr_assert_str_eq(tile->eggs->egg->team->name, "Example Team");
}

Test(get_map, getting_team_eggs)
{
    position_t pos = {0, 0};
    map_t map = create_map(1, 1);
    struct team_s teamA = { "Good guys", 0, 1 };
    struct team_s teamB = { "Mean guys", 0, 1 };

    add_egg_at_position(&teamA, pos, map);
    add_egg_at_position(&teamB, pos, map);
    add_egg_at_position(&teamA, pos, map);
    egg_list_t eggs = get_team_eggs(&teamA, map);
    cr_assert(eggs != NULL);
    uint32_t count = get_list_size((node_t)eggs);
    cr_assert(count == 2);
    cr_assert_str_eq(eggs->egg->team->name, "Good guys");
    cr_assert_str_eq(eggs->next->egg->team->name, "Good guys");
}

Test(get_map, egg_to_player)
{
    team_list_t teams = NULL;
    struct team_s team = { "Good guys", 0, 1 };
    add_to_list((void *)&team, (node_t *)&teams);
    map_t map = create_map(1, 1);
    init_map(map, teams);
    egg_t egg = get_random_egg(&team, map);
    player_t player = egg_to_player(egg, map);
    cr_assert(player != NULL);
    cr_assert_str_eq(player->team->name, "Good guys");
    cr_assert(player->position.x == 0);
    cr_assert(player->position.y == 0);
    cr_assert(player->food == 10);
}
