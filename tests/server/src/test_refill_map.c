/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_refill_map
*/

#include "source_header.h"
#include "zappy.h"

Test(refill_map, empty_map)
{
    map_t map = create_map(10, 10);
    struct server_info_s server_info = {
        .map = map,
        .refill_wait = 0,
        .actual_rocks = (rocks_t){0, 0, 0, 0, 0, 0},
        .actual_food = 0,
        .freq = 1
    };
    server_info.last_refill_check = (struct timespec){0, 0};
    refill_map(&server_info);

    rocks_t rocks = {0, 0, 0, 0, 0, 0};
    uint32_t food = 0;
    tile_t tile;

    for (uint32_t x = 0; x < 10; x++) {
        for (uint32_t y = 0; y < 10; y++) {
            tile = get_tile_at_position((position_t){x, y}, map);
            rocks.deraumere += tile->rocks.deraumere;
            rocks.linemate += tile->rocks.linemate;
            rocks.mendiane += tile->rocks.mendiane;
            rocks.phiras += tile->rocks.phiras;
            rocks.sibur += tile->rocks.sibur;
            rocks.thystame += tile->rocks.thystame;
            food += tile->food;
        }
    }

    cr_assert_neq(server_info.actual_rocks.linemate, 0);
    cr_assert_neq(server_info.actual_rocks.deraumere, 0);
    cr_assert_neq(server_info.actual_rocks.sibur, 0);
    cr_assert_neq(server_info.actual_rocks.mendiane, 0);
    cr_assert_neq(server_info.actual_rocks.phiras, 0);
    cr_assert_neq(server_info.actual_rocks.thystame, 0);
    cr_assert_neq(server_info.actual_food, 0);

    cr_assert_eq(server_info.actual_rocks.linemate, rocks.linemate);
    cr_assert_eq(server_info.actual_rocks.deraumere, rocks.deraumere);
    cr_assert_eq(server_info.actual_rocks.sibur, rocks.sibur);
    cr_assert_eq(server_info.actual_rocks.mendiane, rocks.mendiane);
    cr_assert_eq(server_info.actual_rocks.phiras, rocks.phiras);
    cr_assert_eq(server_info.actual_rocks.thystame, rocks.thystame);
    cr_assert_eq(server_info.actual_food, food);
}


Test(refill_map, full_map)
{
    server_info_t server_info = get_server_info();

    server_info->refill_wait = 0;
    server_info->last_refill_check = (struct timespec){0, 0};
    refill_map(server_info);

    rocks_t new_rocks = {0, 0, 0, 0, 0, 0};
    uint32_t new_food = 0;
    tile_t tile;

    for (uint32_t x = 0; x < server_info->width; x++) {
        for (uint32_t y = 0; y < server_info->height; y++) {
            tile = get_tile_at_position((position_t){x, y}, server_info->map);
            new_rocks.deraumere += tile->rocks.deraumere;
            new_rocks.linemate += tile->rocks.linemate;
            new_rocks.mendiane += tile->rocks.mendiane;
            new_rocks.phiras += tile->rocks.phiras;
            new_rocks.sibur += tile->rocks.sibur;
            new_rocks.thystame += tile->rocks.thystame;
            new_food += tile->food;
        }
    }

    cr_assert_neq(server_info->actual_rocks.linemate, 0);
    cr_assert_neq(server_info->actual_rocks.deraumere, 0);
    cr_assert_neq(server_info->actual_rocks.sibur, 0);
    cr_assert_neq(server_info->actual_rocks.mendiane, 0);
    cr_assert_neq(server_info->actual_rocks.phiras, 0);
    cr_assert_neq(server_info->actual_rocks.thystame, 0);
    cr_assert_neq(server_info->actual_food, 0);

    cr_assert_neq(new_rocks.linemate, 0);
    cr_assert_neq(new_rocks.deraumere, 0);
    cr_assert_neq(new_rocks.sibur, 0);
    cr_assert_neq(new_rocks.mendiane, 0);
    cr_assert_neq(new_rocks.phiras, 0);
    cr_assert_neq(new_rocks.thystame, 0);
    cr_assert_neq(new_food, 0);

    cr_assert_eq(server_info->actual_rocks.linemate, new_rocks.linemate);
    cr_assert_eq(server_info->actual_rocks.deraumere, new_rocks.deraumere);
    cr_assert_eq(server_info->actual_rocks.sibur, new_rocks.sibur);
    cr_assert_eq(server_info->actual_rocks.mendiane, new_rocks.mendiane);
    cr_assert_eq(server_info->actual_rocks.phiras, new_rocks.phiras);
    cr_assert_eq(server_info->actual_rocks.thystame, new_rocks.thystame);
    cr_assert_eq(server_info->actual_food, new_food);
}

Test(refill_map, partially_full_map)
{
    server_info_t server_info = get_server_info();

    server_info->refill_wait = 0;
    server_info->last_refill_check = (struct timespec){0, 0};

    for (uint32_t x = 0; x < 9; x++) {
        for (uint32_t y = 0; y < 9; y++) {
            tile_t tile = get_tile_at_position((position_t){x, y}, server_info->map);
            tile->rocks.linemate = 0;
            tile->rocks.deraumere = 0;
            tile->rocks.sibur = 0;
            tile->rocks.mendiane = 0;
            tile->rocks.phiras = 0;
            tile->rocks.thystame = 0;
            tile->food = 0;
        }
    }

    server_info->actual_rocks = (rocks_t){0, 0, 0, 0, 0, 0};
    server_info->actual_food = 0;
    for (uint32_t x = 0; x < server_info->width; x++) {
        for (uint32_t y = 0; y < server_info->height; y++) {
            tile_t tile = get_tile_at_position((position_t){x, y}, server_info->map);
            server_info->actual_rocks.linemate += tile->rocks.linemate;
            server_info->actual_rocks.deraumere += tile->rocks.deraumere;
            server_info->actual_rocks.sibur += tile->rocks.sibur;
            server_info->actual_rocks.mendiane += tile->rocks.mendiane;
            server_info->actual_rocks.phiras += tile->rocks.phiras;
            server_info->actual_rocks.thystame += tile->rocks.thystame;
            server_info->actual_food += tile->food;
        }
    }

    rocks_t temp_rocks = server_info->actual_rocks;
    uint32_t temp_food = server_info->actual_food;

    refill_map(server_info);

    rocks_t new_rocks = {0, 0, 0, 0, 0, 0};
    uint32_t new_food = 0;

    for (uint32_t x = 0; x < server_info->width; x++) {
        for (uint32_t y = 0; y < server_info->height; y++) {
            tile_t tile = get_tile_at_position((position_t){x, y}, server_info->map);
            new_rocks.linemate += tile->rocks.linemate;
            new_rocks.deraumere += tile->rocks.deraumere;
            new_rocks.sibur += tile->rocks.sibur;
            new_rocks.mendiane += tile->rocks.mendiane;
            new_rocks.phiras += tile->rocks.phiras;
            new_rocks.thystame += tile->rocks.thystame;
            new_food += tile->food;
        }
    }

    cr_assert_eq(server_info->actual_rocks.linemate, new_rocks.linemate);
    cr_assert_eq(server_info->actual_rocks.deraumere, new_rocks.deraumere);
    cr_assert_eq(server_info->actual_rocks.sibur, new_rocks.sibur);
    cr_assert_eq(server_info->actual_rocks.mendiane, new_rocks.mendiane);
    cr_assert_eq(server_info->actual_rocks.phiras, new_rocks.phiras);
    cr_assert_eq(server_info->actual_rocks.thystame, new_rocks.thystame);
    cr_assert_eq(server_info->actual_food, new_food);

    cr_assert_neq(server_info->actual_rocks.linemate, temp_rocks.linemate);
    cr_assert_neq(server_info->actual_rocks.deraumere, temp_rocks.deraumere);
    cr_assert_neq(server_info->actual_rocks.sibur, temp_rocks.sibur);
    cr_assert_neq(server_info->actual_rocks.mendiane, temp_rocks.mendiane);
    cr_assert_neq(server_info->actual_rocks.phiras, temp_rocks.phiras);
    cr_assert_neq(server_info->actual_rocks.thystame, temp_rocks.thystame);
    cr_assert_neq(server_info->actual_food, temp_food);
}
