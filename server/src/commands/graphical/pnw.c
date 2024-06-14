/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pnw
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the new player string
 *
 * @param player the player
 * @return char* the new player string
 */
char *get_new_player_string(const player_t player)
{
    char orientation = get_char_by_orientation(player->orientation);

    return my_snprintf("pnw %d %d %d %c %d %s",
        player->playerNumber, player->position.x, player->position.y,
        orientation, player->level, player->team->name);
}

/**
 * @brief Send the new player to a client
 *
 * @param client the client that executed the command
 * @param player the player
 */
void send_new_player_to_client(const client_t client, const player_t player)
{
    char *new_player_string = get_new_player_string(player);

    queue_buffer(client, new_player_string);
    my_free(new_player_string);
}

/**
 * @brief Send the new player to a client
 *
 * @param client the client that executed the command
 * @param player the player
 */
void send_new_player_to_client_list(const client_list_t clients,
    const player_t player)
{
    client_list_t tmp = clients;
    char *new_player_string = get_new_player_string(player);

    while (tmp) {
        queue_buffer(tmp->client, new_player_string);
        tmp = tmp->next;
    }
    my_free(new_player_string);
}

/**
 * @brief Send the new player to the graphical clients
 *
 * @param player the player
 */
void send_new_player_to_graphical(const player_t player)
{
    client_list_t graphical_clients = get_clients_by_type(GRAPHICAL);

    send_new_player_to_client_list(graphical_clients, player);
}
