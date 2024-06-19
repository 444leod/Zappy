/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_mct
*/

#include "source_header.h"
#include "commands.h"

Test(mct, valid_command_empty_map)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();
    server_info->width = 3;
    server_info->height = 3;
    server_info->map = create_map(3, 3);

    mct((char *[]){"mct", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 9, "bct 0 0 0 0 0 0 0 0 0",
        "bct 1 0 0 0 0 0 0 0 0", "bct 2 0 0 0 0 0 0 0 0",
        "bct 0 1 0 0 0 0 0 0 0", "bct 1 1 0 0 0 0 0 0 0",
        "bct 2 1 0 0 0 0 0 0 0", "bct 0 2 0 0 0 0 0 0 0",
        "bct 1 2 0 0 0 0 0 0 0", "bct 2 2 0 0 0 0 0 0 0");
}

Test(mct, valid_command_random_map)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();
    server_info->width = 3;
    server_info->height = 3;
    server_info->map = create_map(3, 3);
    srand(time(NULL));
    rocks_t rocks = {0, 0, 0, 0, 0, 0};
    uint32_t foods = 0;
    fill_map(server_info->map, &rocks, &foods, server_info->teams);

    mct((char *[]){"mct", NULL}, client, server_info);
    if (!client->packet_queue || !client->packet_queue->packet || !client->packet_queue->packet->buffer)
        cr_assert_fail("Packet queue is empty");
    packet_queue_t packet_queue = client->packet_queue;

    position_t positions[] = {
        {0, 0}, {1, 0}, {2, 0},
        {0, 1}, {1, 1}, {2, 1},
        {0, 2}, {1, 2}, {2, 2},
        {-2, -2}
    };

    for (int i = 0; i < 9; i++) {
        int x = atoi(packet_queue->packet->buffer + 4);
        int y = atoi(packet_queue->packet->buffer + 6);

        int index = 0;
        for (; positions[index].x != -2; index++) {
            if (positions[index].x == x && positions[index].y == y)
                break;
        }
        if (positions[index].x == -2)
            cr_assert_fail("Invalid position");
        tile_t tile = get_tile_at_position(positions[index], server_info->map);
        positions[index].x = -1;
        positions[index].y = -1;
        cr_assert_str_eq(packet_queue->packet->buffer, my_snprintf("bct %d %d %d %d %d %d %d %d %d",
            x, y, tile->food, tile->rocks.linemate, tile->rocks.deraumere,
            tile->rocks.sibur, tile->rocks.mendiane, tile->rocks.phiras,
            tile->rocks.thystame));
        packet_queue = packet_queue->next;
    }
    for (int i = 0; i < 9; i++) {
        cr_assert_eq(positions[i].x, -1);
        cr_assert_eq(positions[i].y, -1);
    }
    cr_assert_null(packet_queue);
}

Test(mct, too_much_parameters)
{
    client_t client = test_create_client(0);
    server_info_t server_info = get_server_info();

    mct((char *[]){"mct", "azuieyaeuy", NULL}, client, server_info);
    assert_packet_queue(client->packet_queue, 1, "sbp");
}
