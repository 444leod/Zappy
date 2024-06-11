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
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    bct((char *[]){"bct", "1", "1", "1", "1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "ko");
}

Test(bct, valid_command_empty_tile)
{
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();
    serverInfo->map = create_map(10, 10);

    tile_t tile = get_tile_at_position((position_t){5, 3}, serverInfo->map);
    tile->rocks = (rocks_t){
        .deraumere = 0,
        .linemate = 0,
        .mendiane = 0,
        .phiras = 0,
        .sibur = 0,
        .thystame = 0,
    };
    tile->food = 0;
    bct((char *[]){"bct", "5", "3", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "bct 5 3 0 0 0 0 0 0 0");
}

Test(bct, valid_command_random_tile1)
{
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();
    serverInfo->map = create_map(10, 10);

    tile_t tile = get_tile_at_position((position_t){5, 3}, serverInfo->map);
    bct((char *[]){"bct", "5", "3", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, my_snprintf("bct 5 3 %d %d %d %d %d %d %d",
        tile->food, tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane, tile->rocks.phiras,
        tile->rocks.thystame));
}

Test(bct, valid_command_random_tile2)
{
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();
    serverInfo->map = create_map(10, 10);

    tile_t tile = get_tile_at_position((position_t){5, 3}, serverInfo->map);
    bct((char *[]){"bct", "5", "3", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, my_snprintf("bct 5 3 %d %d %d %d %d %d %d",
        tile->food, tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane, tile->rocks.phiras,
        tile->rocks.thystame));
}
