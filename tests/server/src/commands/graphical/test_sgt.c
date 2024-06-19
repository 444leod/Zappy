/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_sgt
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(sgt, too_much_arguments)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    sgt((char *[]){"sgt", "0", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: sgt: bad argument number\n");
}

Test(sgt, valid_command1)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    sgt((char *[]){"sgt", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, my_snprintf("sgt %d", server_info->freq));
}

Test(sgt, valid_command2)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    server_info->freq = 100;
    sgt((char *[]){"sgt", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, my_snprintf("sgt %d", server_info->freq));
}
