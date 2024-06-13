/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#include "commands.h"
#include "zappy.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Send the content of a tile to a client via the bct command
 *
 * @param client The client to send the content to
 * @param serverInfo The server info
 * @param position The position of the tile
 */
void send_tile_content(const client_t client,
    const server_info_t serverInfo, const position_t position)
{
    const tile_t tile = get_tile_at_position(position, serverInfo->map);
    char *packet_string = my_snprintf("bct %d %d %d %d %d %d %d %d %d",
        position.x, position.y,
        tile->food,
        tile->rocks.linemate, tile->rocks.deraumere,
        tile->rocks.sibur, tile->rocks.mendiane,
        tile->rocks.phiras, tile->rocks.thystame);

    queue_buffer(client, packet_string);
    my_free(packet_string);
}

/**
 * @brief Get a player by its player number
 *
 * @param playerNumber The player number
 * @return player_t The player
 */
player_t get_player_by_player_number(const uint32_t playerNumber)
{
    client_list_t *clients = get_clients();
    client_list_t clientNode;

    if (!clients)
        return (NULL);
    clientNode = *clients;
    while (clientNode) {
        if (clientNode->client->player &&
            clientNode->client->player->playerNumber == playerNumber)
            return (clientNode->client->player);
        clientNode = clientNode->next;
    }
    return (NULL);
}

/**
 * @brief Get the orientation char by the orientation enum
 *
 * @param orientation The orientation enum
 *
 * @return char The orientation char
 * @return -1 If the orientation is invalid
 */
char get_char_by_orientation(int orientation)
{
    switch (orientation) {
        case 1:
            printf("NORTH\n");
            return ('N');
        case 2:
            printf("EAST\n");
            return ('E');
        case 3:
            printf("SOUTH\n");
            return ('S');
        case 4:
            printf("WEST\n");
            return ('W');
    }
    return -1;
}
