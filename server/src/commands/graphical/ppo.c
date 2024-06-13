/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ppo
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Send the position of a player to a client
 *
 * @param client the client that executed the command
 * @param server_info the server info
 * @param playerNumber the player id
 */
void send_player_pos(const client_t client, const int playerNumber)
{
    player_t player = get_player_by_player_number(playerNumber);
    char orientation;
    char *packet_string;

    if (!player) {
        printf("Client %d: ppo %d: player not found\n",
            client->fd, playerNumber);
        queue_buffer(client, "sbp");
        return;
    }
    orientation = get_char_by_orientation((int)player->orientation);
    packet_string = my_snprintf("ppo %d %d %d %c",
        player->playerNumber,
        player->position.x, player->position.y,
        orientation);
    queue_buffer(client, packet_string);
    my_free(packet_string);
}

/**
 * @brief Ppo command
 * @details Send the position of a player to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void ppo(char **args, const client_t client,
    UNUSED const server_info_t server_info)
{
    int playerNumber;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: ppo: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    playerNumber = atoi(args[1]);
    if (!is_number(args[1]) || playerNumber < 0) {
        printf("Client %d: ppo: argument is not a number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_pos(client, playerNumber);
}
