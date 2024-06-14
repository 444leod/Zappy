/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_take
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(ai_commands, take_unknown)
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
    take(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(ai_commands, take_not_enough)
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
    take(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");

    cr_assert_eq(player.food, 0);
    cr_assert_eq(tile->food, 0);
}

Test(ai_commands, take_food)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    tile_t tile = get_tile_at_position(pos, map);
    tile->food = 50;

    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "food", NULL };
    take(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 1);
    cr_assert_eq(tile->food, 49);
}

Test(ai_commands, take_rock)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    struct player_s player = { 0 };
    struct client_s client = { 0 };

    client.player = &player;
    tile_t tile = get_tile_at_position(pos, map);
    tile->food = 50;
    tile->rocks.sibur = 3;

    server.map = map;
    add_player_at_position(&player, pos, map);

    char *args[2] = { "sibur", NULL };
    take(args, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(player.food, 0);
    cr_assert_eq(tile->food, 50);
    cr_assert_eq(player.rocks.sibur, 1);
    cr_assert_eq(tile->rocks.sibur, 2);
}
