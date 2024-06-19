/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_forward
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(forward_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "forward", "azerty" };

    client.player = &player;
    forward(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(forward_suite, once_north)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    char *args[] = { "", NULL };

    player.orientation = NORTH;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    forward(args, &client, &server);
    cr_assert(player.position.x == 2);
    cr_assert(player.position.y == 1);
    cr_assert_str_eq(client.packet_queue->packet->buffer, "ok");
}

Test(forward_suite, wrap_around_bounds)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 4, 4 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    char *args[] = { "", NULL };

    player.orientation = EAST;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    forward(args, &client, &server);
    cr_assert(player.position.x == 0);
    cr_assert(player.position.y == 4);
    cr_assert_str_eq(client.packet_queue->packet->buffer, "ok");
}
