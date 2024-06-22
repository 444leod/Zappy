/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_bct
*/

#include "source_header.h"
#include "commands.h"

Test(bct, too_much_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    bct((char *[]){"bct", "1", "1", "1", "1", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
    assert_stdout_eq_str("Client 0: bct: bad argument number\n");
}

Test(bct, valid_command_empty_tile)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();
    server_info->map = create_map(10, 10);

    bct((char *[]){"bct", "5", "3", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "bct 5 3 0 0 0 0 0 0 0");
}

Test(bct, valid_command_random_tile1)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();
    server_info->map = create_map(10, 10);
    srand(time(NULL));
    rocks_t rocks = {0, 0, 0, 0, 0, 0};
    uint32_t foods = 0;
    fill_map(server_info->map, &rocks, &foods);

    tile_t tile = get_tile_at_position((position_t){5, 3}, server_info->map);
    bct((char *[]){"bct", "5", "3", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, my_snprintf("bct 5 3 %d %d %d %d %d %d %d",
        tile->food, tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane, tile->rocks.phiras,
        tile->rocks.thystame));
}

Test(bct, valid_command_random_tile2)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();
    server_info->map = create_map(10, 10);
    srand(time(NULL));
    rocks_t rocks = {0, 0, 0, 0, 0, 0};
    uint32_t foods = 0;
    fill_map(server_info->map, &rocks, &foods);

    tile_t tile = get_tile_at_position((position_t){5, 3}, server_info->map);
    bct((char *[]){"bct", "5", "3", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, my_snprintf("bct 5 3 %d %d %d %d %d %d %d",
        tile->food, tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane, tile->rocks.phiras,
        tile->rocks.thystame));
}
