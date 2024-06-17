/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_eject
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(fork_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "Hey" };

    client.player = &player;
    fork_player(args, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(fork_suite, player_fork)
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

Test(fork_suite, two_player_fork)
{
    char *res;
    position_t pos = { 0, 0 };
    struct server_info_s server = { 0 };
    map_t map = create_map(1, 1);

    struct client_s clientA = { 0 };
    struct client_s clientB = { 0 };
    struct player_s playerA = { 0 };
    struct player_s playerB = { 0 };
    struct team_s teamA = { "TeamA", 0, 15 };
    struct team_s teamB = { "TeamB", 0, 15 };

    playerA.team = &teamA;
    clientA.player = &playerA;
    playerB.team = &teamB;
    clientB.player = &playerB;
    server.map = map;
    add_player_at_position(&playerA, pos, map);
    add_player_at_position(&playerB, pos, map);

    fork_player(NULL, &clientA, &server);
    fork_player(NULL, &clientB, &server);

    cr_assert_not_null(clientA.packetQueue);
    cr_assert_not_null(clientA.packetQueue->packet);
    res = clientA.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_not_null(clientB.packetQueue);
    cr_assert_not_null(clientB.packetQueue->packet);
    res = clientB.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    tile_t tile = get_tile_at_position(pos, map);
    uint32_t eggs = get_list_size((node_t)tile->eggs);
    cr_assert_eq(eggs, 2);

    egg_t eggA = get_random_egg(&teamA, map);
    cr_assert_not_null(eggA);
    cr_assert_eq(eggA->pos.x, pos.x);
    cr_assert_eq(eggA->pos.y, pos.y);
    cr_assert_eq(eggA->team, &teamA);

    egg_t eggB = get_random_egg(&teamB, map);
    cr_assert_not_null(eggB);
    cr_assert_eq(eggB->pos.x, pos.x);
    cr_assert_eq(eggB->pos.y, pos.y);
    cr_assert_eq(eggB->team, &teamB);
}

