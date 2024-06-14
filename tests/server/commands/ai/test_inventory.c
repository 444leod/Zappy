/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_inventory
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

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
