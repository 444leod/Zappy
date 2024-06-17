/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_forward
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

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
