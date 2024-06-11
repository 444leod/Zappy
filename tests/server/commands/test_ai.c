/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(ai_commands, forward_north)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = NORTH;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    forward(NULL, &client, &server);
    cr_assert(player.position.x == 2);
    cr_assert(player.position.y == 1);
}

Test(ai_commands, forward_east_bounds)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 4, 4 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = EAST;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    forward(NULL, &client, &server);
    cr_assert(player.position.x == 0);
    cr_assert(player.position.y == 4);
}

Test(ai_commands, right_4_times)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    player.orientation = NORTH;
    client.player = &player;

    right(NULL, &client, NULL);
    cr_assert(player.orientation == EAST);
    right(NULL, &client, NULL);
    cr_assert(player.orientation == SOUTH);
    right(NULL, &client, NULL);
    cr_assert(player.orientation == WEST);
    right(NULL, &client, NULL);
    cr_assert(player.orientation == NORTH);
}

Test(ai_commands, left_4_times)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    player.orientation = NORTH;
    client.player = &player;

    left(NULL, &client, NULL);
    cr_assert(player.orientation == WEST);
    left(NULL, &client, NULL);
    cr_assert(player.orientation == SOUTH);
    left(NULL, &client, NULL);
    cr_assert(player.orientation == EAST);
    left(NULL, &client, NULL);
    cr_assert(player.orientation == NORTH);
}
