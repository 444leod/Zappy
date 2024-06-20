/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_eject
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(connect_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 1, 0, NULL };
    char *args[] = { "connect", "azerty" };

    player.team = &team;
    client.player = &player;
    connect_nbr(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(connect_suite, full)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 1, 0, NULL };
    char *args[] = { "", NULL };

    player.team = &team;
    client.player = &player;
    connect_nbr(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "0");
}

Test(connect_suite, normal)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    struct team_s team = { "Team", 0, 15, NULL };
    char *args[] = { "", NULL };

    player.team = &team;
    client.player = &player;
    connect_nbr(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "15");
}
