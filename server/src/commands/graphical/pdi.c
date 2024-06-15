/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdi
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the player death string
 * @details Get the player death string
 *
 * @param player the player that died
 * @return char* the player death string
 */
char *get_player_death_string(const player_t player)
{
    char *player_death_str = my_snprintf("pdi %d", player->playerNumber);

    return player_death_str;
}

/**
 * @brief Send the player death message to the given client
 * @details Send the player death message to the given client
 *
 * @param client the client
 * @param player the player that died
 */
void send_player_death_to_client(const client_t client, const player_t player)
{
    char *player_death_string = get_player_death_string(player);

    queue_buffer(client, player_death_string);
    my_free(player_death_string);
}

/**
 * @brief Send the player death string to all the clients of the given list
 * @details Send the player death string to all the clients of the given list
 *
 * @param clients the client list
 * @param player the player that died
 */
void send_player_death_to_client_list(const client_list_t clients,
    const player_t player)
{
    char *player_death_string = get_player_death_string(player);
    client_list_t tmp = clients;

    while (tmp) {
        queue_buffer(tmp->client, player_death_string);
        tmp = tmp->next;
    }
    my_free(player_death_string);
}

/**
 * @brief Send to all graphical clients a player death message
 * @details Send to all graphical clients a player death message
 *
 * @param player the player that died
 */
void send_player_death_to_graphical(const player_t player)
{
    const client_list_t graphical_clients = get_clients_by_type(GRAPHICAL);

    send_player_death_to_client_list(graphical_clients, player);
}
