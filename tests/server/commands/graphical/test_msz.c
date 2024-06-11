/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_msz
*/

#include "commands.h"
#include "testing.h"
#include "clients.h"

server_info_t get_server_info()
{
    server_info_t server_info = malloc(sizeof(struct server_info_s));

    add_teams(server_info, (char *[]){"team1", "team2", NULL});

    server_info->height = 10;
    server_info->width = 10;
    server_info->clientsNb = 1;
    return server_info;
}

Test(msz, too_much_parameters)
{
    client_t client = create_client(0);
    client->packetQueue = NULL;
    server_info_t serverInfo = get_server_info();

    msz((char **){"msz", "azuieyaeuy", NULL}, client, serverInfo);
    cr_assert_not_null(client->packetQueue);
    cr_assert_not_null(client->packetQueue->packet);
    cr_assert_not_null(client->packetQueue->packet->buffer);
    cr_assert_str_eq(client->packetQueue->packet->buffer, "ko");
}

Test(msz, valid_command)
{
    client_t client = create_client(0);
    client->packetQueue = NULL;
    server_info_t serverInfo = get_server_info();

    msz((char *[]){"msz", NULL}, client, serverInfo);
    cr_assert_not_null(client->packetQueue);
    cr_assert_not_null(client->packetQueue->packet);
    cr_assert_not_null(client->packetQueue->packet->buffer);
    cr_assert_str_eq(client->packetQueue->packet->buffer, "msz 10 10");
}
