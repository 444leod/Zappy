/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_set
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(ai_commands, set_unknown)
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

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(ai_commands, set_not_enough)
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

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");

    cr_assert_eq(player.food, 0);
    cr_assert_eq(tile->food, 0);
}

Test(ai_commands, set_food)
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

    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "food", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 98);
    cr_assert_eq(tile->food, 1);
}

Test(ai_commands, set_rock)
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
    tile->rocks.sibur = 3;

    server.map = map;
    add_player_at_position(&player, pos, map);
    char *args[2] = { "sibur", NULL };
    set(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 5);
    cr_assert_eq(tile->food, 2);
    cr_assert_eq(player.rocks.sibur, 1);
    cr_assert_eq(tile->rocks.sibur, 4);
}
