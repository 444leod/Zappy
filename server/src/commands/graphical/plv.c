/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** plv
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the player level string
 *
 * @param player the player
 * @return char* the player level string
 */
char *get_player_level_string(const player_t player)
{
    return my_snprintf("plv %d %d", player->playerNumber, player->level);
}

/**
 * @brief Send the player level to a client
 * @details Send the player level to a client
 *
 * @param client the client that executed the command
 * @param playerNumber the player number
*/
void send_player_level_to_client(const client_t client, const int playerNumber)
{
    player_t player = get_player_by_player_number(playerNumber);
    char *player_level_string;

    if (!player) {
        printf("Client %d: plv %d: player not found\n",
            client->fd, playerNumber);
        queue_buffer(client, "sbp");
        return;
    }
    player_level_string = get_player_level_string(player);
    queue_buffer(client, player_level_string);
    my_free(player_level_string);
}

/**
 * @brief Send the player level to a list of clients
 * @details Send the player level to a list of clients
 *
 * @param clients the list of clients
 * @param playerNumber the player number
*/
void send_player_level_to_client_list(const client_list_t clients,
    const int playerNumber)
{
    client_list_t tmp = clients;
    player_t player = get_player_by_player_number(playerNumber);
    char *player_level_string = "sbp";

    if (player)
        player_level_string = get_player_level_string(player);
    else
        printf("GLOBAL: plv %d: player not found\n", playerNumber);
    while (tmp) {
        queue_buffer(tmp->client, player_level_string);
        tmp = tmp->next;
    }
    if (player)
        my_free(player_level_string);
}

/**
 * @brief Plv command
 * @details Send the player level to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
*/
void plv(char **args, const client_t client,
    UNUSED const server_info_t server_info)
{
    int playerNumber;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: plv: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    playerNumber = atoi(args[1]);
    if (!is_number(args[1]) || playerNumber < 0) {
        printf("Client %d: plv: argument is not a number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_level_to_client(client, playerNumber);
}
