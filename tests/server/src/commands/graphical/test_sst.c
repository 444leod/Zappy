/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_sst
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(sst, not_enough_arguments)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    sst((char *[]){"sst", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sst: bad argument number\n");
}

Test(sst, too_much_arguments)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    sst((char *[]){"sst", "0", "0", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sst: bad argument number\n");
}

Test(sst, bad_argument1)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    sst((char *[]){"sst", "azerty", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sst: argument is not a valid number\n");
}

Test(sst, bad_argument2)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    sst((char *[]){"sst", "-1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sst: argument is not a valid number\n");
}

Test(sst, bad_argument3)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    sst((char *[]){"sst", "0", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sst: argument is not a valid number\n");
}

Test(sst, valid_command)
{
    cr_redirect_stdout();
    client_t client1 = test_create_client(0);
    client_t client2 = test_create_client(1);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"GRAPHIC", NULL}, client1, serverInfo);
    auth((char *[]){"GRAPHIC", NULL}, client2, serverInfo);
    client1->packetQueue = NULL;
    client2->packetQueue = NULL;

    sst((char *[]){"sst", "1", NULL}, client1, serverInfo);
    assert_packet_queue(client1->packetQueue, 1, "sst 1");
    assert_packet_queue(client2->packetQueue, 1, "sst 1");
}
