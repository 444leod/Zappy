/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_look
*/

#include "testing.h"
#include "commands.h"
#include "clients.h"

Test(ai_commands, vision_level0)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);

    player.orientation = EAST;
    player.level = 0;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    look(NULL, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player]");
}

Test(ai_commands, vision_level1)
{
    struct client_s client = { 0 };
    struct server_info_s server = { 0 };
    position_t pos = { 2, 2 };
    struct player_s player = { 0 };
    map_t map = create_map(5, 5);
    tile_t tile = get_tile_at_position((position_t){2, 1}, map);

    player.orientation = NORTH;
    player.level = 1;
    server.map = map;
    client.player = &player;
    add_player_at_position(&player, pos, map);
    tile->food = 1;
    tile->rocks.linemate = 1;
    look(NULL, &client, &server);
    char *result = client.packetQueue->packet->buffer;
    cr_assert(result != NULL);
    cr_assert_str_eq(result, "[player,,food linemate,]");
}