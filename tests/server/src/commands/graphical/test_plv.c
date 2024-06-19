/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_plv
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(plv, too_much_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    plv((char *[]){"plv", "1", "zakjeazkjeh", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: plv: bad argument number\n");
}

Test(plv, not_enough_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    plv((char *[]){"plv", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: plv: bad argument number\n");
}

Test(plv, unknown_player)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    plv((char *[]){"plv", "0", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: plv 0: player not found\n");
}

Test(plv, valid_command_level_1)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    auth((char *[]){"teamName", NULL}, client, server_info);
    client->packet_queue = NULL;
    plv((char *[]){"plv", "0", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "plv 0 1");
}

Test(plv, valid_command_level_2)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    auth((char *[]){"teamName", NULL}, client, server_info);
    client->packet_queue = NULL;
    client->player->level = 5;
    plv((char *[]){"plv", "0", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "plv 0 5");
}

Test(plv, valid_command_multiple_players)
{
    cr_redirect_stdout();
    client_t client1 = test_create_client(0);
    client_t client2 = test_create_client(1);
    server_info_t server_info = get_server_info();

    auth((char *[]){"teamName", NULL}, client1, server_info);
    auth((char *[]){"teamName", NULL}, client2, server_info);
    client1->packet_queue = NULL;
    client2->packet_queue = NULL;

    plv((char *[]){"plv", "0", NULL}, client1, server_info);
    assert_packet_queue(client1->packet_queue, 1, "plv 0 1");
    plv((char *[]){"plv", "1", NULL}, client2, server_info);
    assert_packet_queue(client2->packet_queue, 1, "plv 1 1");
}
