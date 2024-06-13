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

void send_player_level(const client_t client, const int playerNumber)
{
    player_t player = get_player_by_player_number(playerNumber);

    if (!player) {
        printf("Client %d: plv %d: player not found\n",
            client->fd, playerNumber);
        queue_buffer(client, "sbp");
        return;
    }
    queue_buffer(client, my_snprintf("plv %d %d",
        player->playerNumber, player->level));
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

    if (tablen((const void **)args) != 1) {
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
    send_player_level(client, playerNumber);
}
