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
            return ('N');
        case 2:
            return ('E');
        case 3:
            return ('S');
        case 4:
            return ('W');
    }
    return -1;
}

/**
 * @brief Queue the given buffer to all the graphical clients
 * @details Queue the given buffer to all the graphical clients
 *
 * @param buffer the buffer to queue
 */
void queue_to_graphical(char *buffer)
{
    client_list_t graphical_clients = get_clients_by_type(GRAPHICAL);

    while (graphical_clients) {
        queue_buffer(graphical_clients->client, buffer);
        graphical_clients = graphical_clients->next;
    }
    my_free(buffer);
}
