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
 * @param player_number The player number
 * @return player_t The player
 */
player_t get_player_by_player_number(const uint32_t player_number)
{
    client_list_t *clients = get_clients();
    client_list_t client_node;

    if (!clients)
        return (NULL);
    client_node = *clients;
    while (client_node) {
        if (client_node->client->player &&
            client_node->client->player->player_number == player_number)
            return (client_node->client->player);
        client_node = client_node->next;
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
