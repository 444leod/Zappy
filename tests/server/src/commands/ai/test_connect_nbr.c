/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_eject
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

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
