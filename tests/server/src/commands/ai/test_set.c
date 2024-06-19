/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_set
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(set_suite, no_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { NULL };

    client.player = &player;
    set(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(set_suite, unknown)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "zorglub's sword", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(set_suite, not_enough)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    tile_t tile = get_tile_at_position(pos, map);
    tile->food = 0;

    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "food", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");

    cr_assert_eq(player.food, 0);
    cr_assert_eq(tile->food, 0);
}

Test(set_suite, food)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    tile_t tile = get_tile_at_position(pos, map);
    player.food = 99;
    tile->food = 0;
    server.actual_food = 0;

    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "food", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 98);
    cr_assert_eq(tile->food, 1);
    cr_assert_eq(server.actual_food, 1);
}

Test(set_suite, rock)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    tile_t tile = get_tile_at_position(pos, map);
    player.food = 5;
    player.rocks.sibur = 2;
    tile->food = 2;
    server.actual_food = 2;
    tile->rocks.sibur = 3;
    server.actual_rocks.sibur = 3;

    server.map = map;
    add_player_at_position(&player, pos, map);
    char *args[2] = { "sibur", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 5);
    cr_assert_eq(tile->food, 2);
    cr_assert_eq(server.actual_food, 2);

    cr_assert_eq(player.rocks.sibur, 1);
    cr_assert_eq(tile->rocks.sibur, 4);
    cr_assert_eq(server.actual_rocks.sibur, 4);
}
