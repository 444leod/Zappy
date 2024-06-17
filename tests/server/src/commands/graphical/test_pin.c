/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_pin
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(pin, not_enough_arguments)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    pin((char *[]){"pin", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: pin: bad argument number\n");
}

Test(pin, too_much_arguments)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    pin((char *[]){"pin", "0", "0", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: pin: bad argument number\n");
}

Test(pin, invalid_argument)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    pin((char *[]){"pin", "azerty", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: pin: argument is not a valid number\n");
}

Test(pin, valid_command)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client, serverInfo);
    client->packetQueue = NULL;
    pin((char *[]){"pin", "0", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "pin 0 10 0 0 0 0 0 0");
}

Test(pin, valid_command_multiple_players)
{
    cr_redirect_stdout();
    client_t client1 = test_create_client(0);
    client_t client2 = test_create_client(1);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client1, serverInfo);
    auth((char *[]){"teamName", NULL}, client2, serverInfo);
    client1->packetQueue = NULL;
    client2->packetQueue = NULL;
    client1->player->food = 5;
    client1->player->rocks.linemate = 1;
    client1->player->rocks.deraumere = 2;
    client1->player->rocks.sibur = 3;
    client1->player->rocks.mendiane = 0;

    client2->player->food = 3;
    client2->player->rocks.linemate = 27;
    client2->player->rocks.deraumere = 0;
    client2->player->rocks.sibur = 2;
    client2->player->rocks.mendiane = 99;

    pin((char *[]){"pin", "0", NULL}, client1, serverInfo);
    assert_packet_queue(client1->packetQueue, 1, "pin 0 5 1 2 3 0 0 0");
    pin((char *[]){"pin", "1", NULL}, client2, serverInfo);
    assert_packet_queue(client2->packetQueue, 1, "pin 1 3 27 0 2 99 0 0");
}

Test(pin, invalid_player_id1)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    pin((char *[]){"pin", "-1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: pin: argument is not a valid number\n");
}

Test(pin, invalid_player_id2)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    pin((char *[]){"pin", "1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: pin 1: player not found\n");
}
