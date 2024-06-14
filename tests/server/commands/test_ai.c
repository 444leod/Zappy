/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"
#include "lib.h"

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
    cr_assert_str_eq(client.packetQueue->packet->buffer, "ok");
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
    cr_assert_str_eq(client.packetQueue->packet->buffer, "ok");
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

    packet_queue_t queue = client.packetQueue;
    uint32_t qsize = 0;
    while (queue != NULL) {
        cr_assert_str_eq(queue->packet->buffer, "ok");
        qsize++;
        queue = queue->next;
    }
    cr_assert_eq(qsize, 4);
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

    packet_queue_t queue = client.packetQueue;
    uint32_t qsize = 0;
    while (queue != NULL) {
        cr_assert_str_eq(queue->packet->buffer, "ok");
        qsize++;
        queue = queue->next;
    }
    cr_assert_eq(qsize, 4);
}

Test(ai_commands, vision_level0)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = EAST;
    player.level = 0;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    look(NULL, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player]");
}

Test(ai_commands, vision_level1)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    tile_t tile = get_tile_at_position((position_t){2, 1}, map);

    player.orientation = NORTH;
    player.level = 1;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    tile->food = 1;
    tile->rocks.linemate = 1;
    look(NULL, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player,,food linemate,]");
}

Test(ai_commands, empty_inventory)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    client.player = &player;
    inventory(NULL, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[]");
}

Test(ai_commands, inventory_single)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    client.player = &player;
    player.rocks.linemate = 5;
    inventory(NULL, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[linemate 5]");
}

Test(ai_commands, inventory_multiple)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    client.player = &player;
    player.rocks.linemate = 5;
    player.rocks.phiras = 2;
    inventory(NULL, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[linemate 5,phiras 2]");
}

Test(ai_commands, connect_nbr_no_team)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };

    client.player = &player;
    connect_nbr(NULL, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(ai_commands, connect_nbr_full)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 1, 0 };

    player.team = &team;
    client.player = &player;
    connect_nbr(NULL, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "0");
}

Test(ai_commands, connect_nbr_some)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 0, 15 };

    player.team = &team;
    client.player = &player;
    connect_nbr(NULL, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "15");
}

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

Test(ai_commands, player_eject_ko)
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
    eject(NULL, &client, &server);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(ai_commands, player_eject_ok)
{
    position_t pos = { 2, 3 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);

    struct player_s playerA = { 0 };
    struct player_s playerB = { 0 };
    struct client_s clientA = { 0 };
    struct client_s clientB = { 0 };
    struct team_s teamA = { "Team A", 0, 15 };
    struct team_s teamB = { "Team B", 0, 15 };

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

    eject(NULL, &clientA, &server);

    cr_assert_not_null(clientA.packetQueue);
    cr_assert_not_null(clientA.packetQueue->packet);
    char *res = clientA.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ok");

    cr_assert_eq(clientB.player->position.x, 1);
    cr_assert_eq(clientB.player->position.y, 3);

    cr_assert_not_null(clientB.packetQueue);
    cr_assert_not_null(clientB.packetQueue->packet);
    res = clientB.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "eject: 2");

    cr_assert_eq(get_list_size((node_t)tile->players), 1);
    cr_assert_eq(get_list_size((node_t)tile->eggs), 0);
}

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
