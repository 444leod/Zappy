/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_incantation
*/


#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(incantation_suite, start_bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "incantation", "azerty" };

    client.player = &player;
    start_incantation(args, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(incantation_suite, start_bad_level)
{
    char *res = NULL;
    position_t pos = { 0, 0 };
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    map_t map = create_map(1, 1);
    struct server_info_s server = { 0 };
    char *args[] = { "", NULL };

    player.position = pos;
    player.level = 0;
    client.player = &player;
    server.map = map;
    add_player_at_position(&player, pos, map);

    start_incantation(args, &client, &server);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");

    player.level = 8;
    client.player = &player;
    server.map = map;
    add_player_at_position(&player, pos, map);

    start_incantation(args, &client, &server);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(incantation_suite, start_no_ressources)
{
    position_t pos = { 0, 0 };
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    map_t map = create_map(1, 1);
    struct server_info_s server = { 0 };
    tile_t tile = get_tile_at_position(pos, map);
    char *args[] = { "", NULL };

    player.level = 1;
    client.player = &player;
    server.map = map;
    tile->food = 9;
    tile->rocks = (rocks_t){ 0, 9, 9, 9, 9, 9 };
    add_player_at_position(&player, pos, map);

    start_incantation(args, &client, &server);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(incantation_suite, start_enough_ressources)
{
    position_t pos = { 0, 0 };
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    map_t map = create_map(1, 1);
    struct server_info_s server = { 0 };
    tile_t tile = get_tile_at_position(pos, map);
    char *args[] = { "", NULL };

    add_client(&client);

    player.level = 1;
    client.player = &player;
    server.map = map;
    tile->food = 0;
    tile->rocks = (rocks_t){ 1, 0, 0, 0, 0, 0 };
    add_player_at_position(&player, pos, map);

    start_incantation(args, &client, &server);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "Elevation underway");
}
