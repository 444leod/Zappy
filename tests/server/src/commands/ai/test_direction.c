/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_forward
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(right_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "right", "azerty" };

    client.player = &player;
    right(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(right_suite, repeat)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    player.orientation = NORTH;
    client.player = &player;

    right(args, &client, NULL);
    cr_assert(player.orientation == EAST);
    right(args, &client, NULL);
    cr_assert(player.orientation == SOUTH);
    right(args, &client, NULL);
    cr_assert(player.orientation == WEST);
    right(args, &client, NULL);
    cr_assert(player.orientation == NORTH);

    packet_queue_t queue = client.packet_queue;
    uint32_t qsize = 0;
    while (queue != NULL) {
        cr_assert_str_eq(queue->packet->buffer, "ok");
        qsize++;
        queue = queue->next;
    }
    cr_assert_eq(qsize, 4);
}

Test(left_suite, bad_arguments)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "left", "azerty" };

    client.player = &player;
    left(args, &client, NULL);

    cr_assert_not_null(client.packet_queue);
    cr_assert_not_null(client.packet_queue->packet);
    char *res = client.packet_queue->packet->buffer;
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "ko");
}

Test(left_suite, repeat)
{
    struct client_s client = { 0 };
    struct player_s player = { 0 };
    char *args[] = { "", NULL };

    player.orientation = NORTH;
    client.player = &player;

    left(args, &client, NULL);
    cr_assert(player.orientation == WEST);
    left(args, &client, NULL);
    cr_assert(player.orientation == SOUTH);
    left(args, &client, NULL);
    cr_assert(player.orientation == EAST);
    left(args, &client, NULL);
    cr_assert(player.orientation == NORTH);

    packet_queue_t queue = client.packet_queue;
    uint32_t qsize = 0;
    while (queue != NULL) {
        cr_assert_str_eq(queue->packet->buffer, "ok");
        qsize++;
        queue = queue->next;
    }
    cr_assert_eq(qsize, 4);
}
