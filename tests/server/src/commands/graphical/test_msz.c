/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_msz
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(msz, too_much_parameters)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    msz((char *[]){"msz", "azuieyaeuy", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
}

Test(msz, valid_command)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    msz((char *[]){"msz", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "msz 10 10");
}
