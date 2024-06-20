/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_eject
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(eject_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "eject", "azerty" };

    client.player = &player;
    eject(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(eject_suite, alone)
{
    position_t pos = { 2, 3 };
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 0, 15, NULL };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    char *args[] = { "", NULL };

    player.team = &team;
    client.player = &player;
    server.map = map;
    add_player_at_position(&player, pos, map);
    eject(args, &client, &server);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(eject_suite, normal)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);
    char *args[] = { "", NULL };

    struct player_s playerA = { 0 };
    struct player_s playerB = { 0 };
    struct client_s clientA = { 0 };
    struct client_s clientB = { 0 };
    struct team_s teamA = { "Team A", 0, 15, NULL };
    struct team_s teamB = { "Team B", 0, 15, NULL };

    playerA.orientation = EAST;
    playerA.team = &teamA;
    clientA.player = &playerA;
    playerB.team = &teamB;
    clientB.player = &playerB;

    uuid_generate(playerA.id);
    add_client(&clientA);
    uuid_generate(playerB.id);
    add_client(&clientB);
    server.map = map;
    add_player_at_position(&playerA, pos, map);
    add_player_at_position(&playerB, pos, map);
    add_egg_at_position(&teamA, pos, map);

    tile_t tile = get_tile_at_position(pos, map);
    cr_assert_eq(get_list_size((node_t)tile->players), 2);
    cr_assert_eq(get_list_size((node_t)tile->eggs), 1);

    eject(args, &clientA, &server);

    cr_assert_not_null(clientA.packet_queue);
    cr_assert_not_null(clientA.packet_queue->packet);
    char *res = clientA.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(clientB.player->position.x, 1);
    cr_assert_eq(clientB.player->position.y, 3);

    cr_assert_not_null(clientB.packet_queue);
    cr_assert_not_null(clientB.packet_queue->packet);
    res = clientB.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "eject: 2");

    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(get_list_size((node_t)tile->eggs), 0);
}
