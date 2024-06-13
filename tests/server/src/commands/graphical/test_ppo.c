/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_ppo
*/

#include "source_header.h"
#include "commands.h"
#include "clients.h"

Test(ppo, too_much_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    ppo((char *[]){"ppo", "azuieyae", "aze", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: ppo: bad argument number\n");
}

Test(ppo, valid_command)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client, serverInfo);
    client->packetQueue = NULL;
    ppo((char *[]){"ppo", "0", NULL}, client, serverInfo);
    position_t pos = client->player->position;
    assert_packet_queue(client->packetQueue, 1, my_snprintf("ppo 0 %d %d N", pos.x, pos.y));
}

Test(ppo, valid_command_multiple_players)
{
    cr_redirect_stdout();
    client_t client1 = test_create_client(0);
    client_t client2 = test_create_client(1);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client1, serverInfo);
    auth((char *[]){"teamName", NULL}, client2, serverInfo);
    client1->packetQueue = NULL;
    client2->packetQueue = NULL;

    ppo((char *[]){"ppo", "1", NULL}, client1, serverInfo);
    position_t pos = client2->player->position;
    enum ORIENTATION ori = client2->player->orientation;
    char orientationChar = '0';
    switch (ori) {
        case NORTH:
            orientationChar = 'N';
            break;
        case SOUTH:
            orientationChar = 'S';
            break;
        case EAST:
            orientationChar = 'E';
            break;
        case WEST:
            orientationChar = 'W';
            break;
    }
    assert_packet_queue(client1->packetQueue, 1, my_snprintf("ppo 1 %d %d %c", pos.x, pos.y, orientationChar));
}

Test(ppo, not_enough_parameters)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    ppo((char *[]){"ppo", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: ppo: bad argument number\n");
}

Test(ppo, invalid_player_id1)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    ppo((char *[]){"ppo", "1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: ppo 1: player not found\n");
}

Test(ppo, invalid_player_id2)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client, serverInfo);
    client->packetQueue = NULL;
    ppo((char *[]){"ppo", "1", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: Connected as teamName\nClient 0: ppo 1: player not found\n");
}

Test(ppo, invalid_player_id3)
{
    cr_redirect_stdout();
    client_t client = test_create_client(0);
    server_info_t serverInfo = get_server_info();

    auth((char *[]){"teamName", NULL}, client, serverInfo);

    client->packetQueue = NULL;
    ppo((char *[]){"ppo", "azeazeazeaeazeaeaz", NULL}, client, serverInfo);
    assert_packet_queue(client->packetQueue, 1, "sbp");
    assert_stdout_eq_str("Client 0: Connected as teamName\nClient 0: ppo: argument is not a number\n");
}