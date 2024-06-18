/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_look
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(look_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "look", "azerty" };

    client.player = &player;
    look(args, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(look_suite, level_zero)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    char *args[] = { "", NULL };

    player.orientation = EAST;
    player.level = 0;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    look(args, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player]");
}

Test(look_suite, level_one)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    tile_t tile = get_tile_at_position((position_t){2, 1}, map);
    char *args[] = { "", NULL };

    player.orientation = NORTH;
    player.level = 1;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    tile->food = 1;
    tile->rocks.linemate = 1;
    look(args, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player,,food linemate,]");
}