/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** authentification tests
*/

#include "testing.h"
#include <sys/wait.h>
#include "zappy.h"
#include "commands.h"
#include "linked_lists.h"

Test(auth, valid_ai_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"teamName", NULL};

    auth(args, client, server_info);
    cr_assert_not_null(client->player);
    cr_assert_not_null(client->player->team);
    cr_assert(client->player->team->actualNumber == 1);
    cr_assert(client->player->team->remainingSlots == 9);
    cr_assert(client->type == AI);
    cr_assert(client->clientNumber == 0);
    assert_packet_queue(client->packetQueue, 2, "9", "10 10");
    assert_stdout_eq_str("Client 0: Connected as teamName\n");
}

Test(auth, valid_graphical_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"GRAPHIC", NULL};

    auth(args, client, server_info);
    cr_assert(client->type == GRAPHICAL);
    cr_assert(client->clientNumber == 0);
    cr_assert_null(client->player);
    assert_packet_queue(client->packetQueue, 1, "ok");
    assert_stdout_eq_str("Client 0: Connected as GRAPHIC\n");
}

Test(auth, invalid_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"team3", NULL};

    auth(args, client, server_info);
    cr_assert_null(client->player);
    cr_assert(client->type == NONE);
    assert_packet_queue(client->packetQueue, 1, "ko");
    assert_stdout_eq_str("Client 0: Invalid team name (team3)\n");
}

Test(auth, full_team)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"teamName", NULL};

    server_info->teams->team->remainingSlots = 0;
    auth(args, client, server_info);
    cr_assert_null(client->player);
    cr_assert(client->type == NONE);
    assert_packet_queue(client->packetQueue, 1, "ko");
    assert_stdout_eq_str("Client 0: Team teamName is full\n");
}

Test(auth, no_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {NULL};

    auth(args, client, server_info);
    cr_assert_null(client->player);
    cr_assert(client->type == NONE);
    assert_packet_queue(client->packetQueue, 1, "ko");
    assert_stdout_eq_str("Client 0: Bad team name\n");
}

Test(auth, multiple_args)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"team1", "team2", NULL};

    auth(args, client, server_info);
    cr_assert_null(client->player);
    cr_assert(client->type == NONE);
    assert_packet_queue(client->packetQueue, 1, "ko");
    assert_stdout_eq_str("Client 0: Bad team name\n");
}
