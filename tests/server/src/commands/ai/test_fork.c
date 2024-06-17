/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_eject
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(ai_commands, player_fork)
{
    position_t pos = { 2, 3 };
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 0, 15 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);

    player.team = &team;
    client.player = &player;
    server.map = map;
    add_player_at_position(&player, pos, map);
    fork_player(NULL, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    egg_t egg = get_random_egg(&team, map);
    cr_assert_not_null(egg);
    cr_assert_eq(egg->pos.x, pos.x);
    cr_assert_eq(egg->pos.y, pos.y);
    cr_assert_eq(egg->team, &team);
}
