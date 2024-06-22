/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_broadcast
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(broadcast_suite, get_hearing_north_one)
{
    struct player_s player = { 0 };
    struct client_s client = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = NORTH;
    player.position = (position_t){2, 2};
    client.player = &player;
    add_client(&client);

    position_t pos = get_hearing_square(&player, 1, map);
    cr_assert_eq(pos.x, 2);
    cr_assert_eq(pos.y, 1);
}

Test(broadcast_suite, get_hearing_west_three)
{
    struct player_s player = { 0 };
    struct client_s client = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = WEST;
    player.position = (position_t){2, 2};
    client.player = &player;
    add_client(&client);

    position_t pos = get_hearing_square(&player, 3, map);
    cr_assert_eq(pos.x, 2);
    cr_assert_eq(pos.y, 3);
}

Test(broadcast_suite, get_hearing_east_six)
{
    struct player_s player = { 0 };
    struct client_s client = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = EAST;
    player.position = (position_t){2, 2};
    client.player = &player;
    add_client(&client);

    position_t pos = get_hearing_square(&player, 6, map);
    cr_assert_eq(pos.x, 1);
    cr_assert_eq(pos.y, 3);
}

Test(broadcast_suite, broadcast_face_to_face)
{
    struct player_s playerA = { 0 };
    struct player_s playerB = { 0 };
    struct client_s clientA = { 0 };
    struct client_s clientB = { 0 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);

    server.map = map;
    playerB.orientation = WEST;
    playerA.position = (position_t){2, 2};
    playerB.position = (position_t){3, 2};
    clientA.player = &playerA;
    clientB.player = &playerB;
    add_client(&clientA);
    add_client(&clientB);

    char *args[] = { "broadcast", "Hello World!", NULL };
    broadcast(args, &clientA, &server);

    cr_assert_not_null(clientA.packet_queue);
    cr_assert_not_null(clientA.packet_queue->packet);
    cr_assert_str_eq(clientA.packet_queue->packet->buffer, "ok");

    cr_assert_not_null(clientB.packet_queue);
    cr_assert_not_null(clientB.packet_queue->packet);
    cr_assert_str_eq(
        clientB.packet_queue->packet->buffer,
        "message 1, Hello World!");
}

Test(broadcast_suite, broadcast_with_wrap)
{
    struct player_s playerA = { 0 };
    struct player_s playerB = { 0 };
    struct client_s clientA = { 0 };
    struct client_s clientB = { 0 };
    struct server_info_s server = { 0 };
    map_t map = create_map(5, 5);

    server.map = map;
    playerB.orientation = WEST;
    playerA.position = (position_t){1, 2};
    playerB.position = (position_t){4, 2};
    clientA.player = &playerA;
    clientB.player = &playerB;
    add_client(&clientA);
    add_client(&clientB);

    char *args[] = { "broadcast", "Hello World!", NULL };
    broadcast(args, &clientA, &server);

    cr_assert_not_null(clientA.packet_queue);
    cr_assert_not_null(clientA.packet_queue->packet);
    cr_assert_str_eq(clientA.packet_queue->packet->buffer, "ok");

    cr_assert_not_null(clientB.packet_queue);
    cr_assert_not_null(clientB.packet_queue->packet);
    cr_assert_str_eq(
        clientB.packet_queue->packet->buffer,
        "message 5, Hello World!");
}
