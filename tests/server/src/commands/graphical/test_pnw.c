/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_pnw
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"
#include "commands_utils.h"

Test(pnw, new_player_to_1_graphical)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t ai_client = test_create_client(0);
    client_t graphical_client = test_create_client(1);

    auth((char *[]){"GRAPHIC", NULL}, graphical_client, server_info);
    graphical_client->packetQueue = NULL;
    auth((char *[]){"teamName", NULL}, ai_client, server_info);
    cr_assert_not_null(ai_client->player);
    cr_assert_not_null(ai_client->player->team);
    cr_assert_eq(ai_client->player->team->actualNumber, 1);
    cr_assert_eq(ai_client->player->team->remainingSlots, 9);
    cr_assert_eq(ai_client->type, AI);
    cr_assert_eq(ai_client->teamClientNumber, 0);
    cr_assert_eq(ai_client->player->playerNumber, 0);
    assert_packet_queue(ai_client->packetQueue, 2, "9", "10 10");

    cr_assert_null(graphical_client->player);
    cr_assert_eq(graphical_client->type, GRAPHICAL);

    assert_packet_queue(graphical_client->packetQueue, 1, my_snprintf("pnw %d %d %d %c %d %s",
        ai_client->player->playerNumber, ai_client->player->position.x,
        ai_client->player->position.y, get_char_by_orientation(ai_client->player->orientation),
        ai_client->player->level, ai_client->player->team->name));
}

Test(pnw, new_player_to_2_graphical)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t ai_client = test_create_client(0);
    client_t graphical_client = test_create_client(1);
    client_t graphical_client2 = test_create_client(2);

    auth((char *[]){"GRAPHIC", NULL}, graphical_client, server_info);
    auth((char *[]){"GRAPHIC", NULL}, graphical_client2, server_info);
    graphical_client->packetQueue = NULL;
    graphical_client2->packetQueue = NULL;
    auth((char *[]){"teamName", NULL}, ai_client, server_info);
    cr_assert_not_null(ai_client->player);
    cr_assert_not_null(ai_client->player->team);
    cr_assert_eq(ai_client->player->team->actualNumber, 1);
    cr_assert_eq(ai_client->player->team->remainingSlots, 9);
    cr_assert_eq(ai_client->type, AI);
    cr_assert_eq(ai_client->teamClientNumber, 0);
    cr_assert_eq(ai_client->player->playerNumber, 0);
    assert_packet_queue(ai_client->packetQueue, 2, "9", "10 10");

    cr_assert_null(graphical_client->player);
    cr_assert_eq(graphical_client->type, GRAPHICAL);
    cr_assert_null(graphical_client2->player);
    cr_assert_eq(graphical_client2->type, GRAPHICAL);

    assert_packet_queue(graphical_client->packetQueue, 1, my_snprintf("pnw %d %d %d %c %d %s",
        ai_client->player->playerNumber, ai_client->player->position.x,
        ai_client->player->position.y, get_char_by_orientation(ai_client->player->orientation),
        ai_client->player->level, ai_client->player->team->name));
    assert_packet_queue(graphical_client2->packetQueue, 1, my_snprintf("pnw %d %d %d %c %d %s",
        ai_client->player->playerNumber, ai_client->player->position.x,
        ai_client->player->position.y, get_char_by_orientation(ai_client->player->orientation),
        ai_client->player->level, ai_client->player->team->name));
}
