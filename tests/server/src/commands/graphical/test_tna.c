/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_tna
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(tna, too_much_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    tna((char *[]){"tna", "azuieyaeuy", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: tna: bad argument number\n");
}

Test(tna, valid_command)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    tna((char *[]){"tna", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "tna teamName\ntna team2");
}
