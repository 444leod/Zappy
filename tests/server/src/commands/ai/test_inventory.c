/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_inventory
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(inventory_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "inventory", "azerty" };

    client.player = &player;
    inventory(args, &client, NULL);

    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(inventory_suite, empty_inventory)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    client.player = &player;
    inventory(args, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);

    cr_assert_str_eq(res,
        "[food 0, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]");
}

Test(inventory_suite, inventory_single_rock)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    client.player = &player;
    player.rocks.linemate = 5;
    inventory(args, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);

    cr_assert_str_eq(res,
        "[food 0, linemate 5, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]");
}

Test(inventory_suite, inventory_single_food)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    client.player = &player;
    player.food = 9;
    inventory(args, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);

    cr_assert_str_eq(res,
        "[food 9, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]");
}

Test(inventory_suite, inventory_multiple)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    client.player = &player;
    player.food = 65;
    player.rocks.linemate = 5;
    player.rocks.phiras = 2;
    inventory(args, &client, NULL);
    cr_assert_not_null(client.packetQueue);
    cr_assert_not_null(client.packetQueue->packet);
    char *res = client.packetQueue->packet->buffer;
    cr_assert_not_null(res);

    cr_assert_str_eq(res,
        "[food 65, linemate 5, deraumere 0, sibur 0, mendiane 0, phiras 2, thystame 0]");
}
