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

void add_teams(server_info_t server_info, char **teams)
{
    team_t team;

    server_info->teams = NULL;
    for (uint32_t i = 0; teams[i]; i++) {
        team = malloc(sizeof(struct team_s));
        team->name = strdup(teams[i]);
        team->actualNumber = 0;
        team->remainingSlots = 1;
        add_to_list((void *)team, (node_t *)&server_info->teams);
    }
}

server_info_t get_server_info()
{
    server_info_t server_info = malloc(sizeof(struct server_info_s));

    add_teams(server_info, (char *[]){"team1", "team2", NULL});

    server_info->height = 10;
    server_info->width = 10;
    server_info->clientsNb = 1;
    return server_info;
}

void assert_packet_queue(client_t client, uint32_t packets_number, ...)
{
    packet_queue_t packet_queue = client->packetQueue;
    va_list args;

    va_start(args, packets_number);
    for (uint32_t i = 0; i < packets_number; i++) {
        cr_assert_not_null(packet_queue);
        cr_assert_not_null(packet_queue->packet);
        cr_assert_not_null(packet_queue->packet->buffer);
        cr_assert_str_eq(packet_queue->packet->buffer, va_arg(args, char *));
        packet_queue = packet_queue->next;
    }
    cr_assert_null(packet_queue);
    va_end(args);
}

Test(auth, valid_ai_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"team1", NULL};

    auth(args, client, server_info);
    cr_assert(client->team != NULL);
    cr_assert(client->team->actualNumber == 1);
    cr_assert(client->team->remainingSlots == 0);
    cr_assert(client->type == AI);
    cr_assert(client->clientNumber == 0);
    assert_packet_queue(client, 2, "0", "10 10");
    assert_stdout_eq_str("Client 0: Connected as team1\n");
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
    cr_assert(client->team == NULL);
    cr_assert(client->clientNumber == 0);
    assert_packet_queue(client, 1, "ok");
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
    cr_assert(client->team == NULL);
    cr_assert(client->type == NONE);
    assert_packet_queue(client, 1, "ko");
    assert_stdout_eq_str("Client 0: Invalid team name (team3)\n");
}

Test(auth, full_team)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {"team1", NULL};

    server_info->teams->team->remainingSlots = 0;
    auth(args, client, server_info);
    cr_assert(client->team == NULL);
    cr_assert(client->type == NONE);
    assert_packet_queue(client, 1, "ko");
    assert_stdout_eq_str("Client 0: Team team1 is full\n");
}

Test(auth, no_team_name)
{
    cr_redirect_stdout();
    server_info_t server_info = get_server_info();
    client_t client = create_client(0);
    client->packetQueue = NULL;
    char *args[] = {NULL};

    auth(args, client, server_info);
    cr_assert(client->team == NULL);
    cr_assert(client->type == NONE);
    assert_packet_queue(client, 1, "ko");
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
    cr_assert(client->team == NULL);
    cr_assert(client->type == NONE);
    assert_packet_queue(client, 1, "ko");
    assert_stdout_eq_str("Client 0: Bad team name\n");
}
