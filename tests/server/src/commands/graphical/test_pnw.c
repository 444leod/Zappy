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
    graphical_client->packet_queue = NULL;
    auth((char *[]){"teamName", NULL}, ai_client, server_info);
    cr_assert_not_null(ai_client->player);
    cr_assert_not_null(ai_client->player->team);
    cr_assert_eq(ai_client->player->team->actual_number, 1);
    cr_assert_eq(ai_client->player->team->remaining_slots, 9);
    cr_assert_eq(ai_client->type, AI);
    cr_assert_eq(ai_client->team_client_number, 0);
    cr_assert_eq(ai_client->player->player_number, 0);
    assert_packet_queue(ai_client->packet_queue, 2, "9", "10 10");

    cr_assert_null(graphical_client->player);
    cr_assert_eq(graphical_client->type, GRAPHICAL);

    char *egg_player_connexion_string = my_snprintf("ebo %d", ai_client->player->egg_number);
    char *new_connexion_string = my_snprintf("pnw %d %d %d %c %d %s",
        ai_client->player->player_number, ai_client->player->position.x,
        ai_client->player->position.y, get_char_by_orientation(ai_client->player->orientation),
        ai_client->player->level, ai_client->player->team->name);

    assert_packet_queue(graphical_client->packet_queue, 2, egg_player_connexion_string, new_connexion_string);
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
    graphical_client->packet_queue = NULL;
    graphical_client2->packet_queue = NULL;
    auth((char *[]){"teamName", NULL}, ai_client, server_info);
    cr_assert_not_null(ai_client->player);
    cr_assert_not_null(ai_client->player->team);
    cr_assert_eq(ai_client->player->team->actual_number, 1);
    cr_assert_eq(ai_client->player->team->remaining_slots, 9);
    cr_assert_eq(ai_client->type, AI);
    cr_assert_eq(ai_client->team_client_number, 0);
    cr_assert_eq(ai_client->player->player_number, 0);
    assert_packet_queue(ai_client->packet_queue, 2, "9", "10 10");

    cr_assert_null(graphical_client->player);
    cr_assert_eq(graphical_client->type, GRAPHICAL);
    cr_assert_null(graphical_client2->player);
    cr_assert_eq(graphical_client2->type, GRAPHICAL);

    char *egg_player_connexion_string = my_snprintf("ebo %d", ai_client->player->egg_number);

    char *new_connexion_string = my_snprintf("pnw %d %d %d %c %d %s",
        ai_client->player->player_number, ai_client->player->position.x,
        ai_client->player->position.y, get_char_by_orientation(ai_client->player->orientation),
        ai_client->player->level, ai_client->player->team->name);

    assert_packet_queue(graphical_client->packet_queue, 2, egg_player_connexion_string, new_connexion_string);
    assert_packet_queue(graphical_client2->packet_queue, 2, egg_player_connexion_string, new_connexion_string);
}
