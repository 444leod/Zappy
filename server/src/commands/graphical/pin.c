/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pin
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Send the player inventory to a client
 * @details Send the player inventory to a client
 *
 * @param client the client that executed the command
 * @param playerNumber the player number
*/
void send_player_inventory(const client_t client, const int playerNumber)
{
    player_t player = get_player_by_player_number(playerNumber);
    char *inventory;

    if (!player) {
        printf("Client %d: pin %d: player not found\n",
            client->fd, playerNumber);
        queue_buffer(client, "sbp");
        return;
    }
    inventory = my_snprintf("pin %d %d %d %d %d %d %d %d",
        player->playerNumber, player->food,
        player->rocks.linemate, player->rocks.deraumere,
        player->rocks.sibur, player->rocks.mendiane,
        player->rocks.phiras, player->rocks.thystame);
    queue_buffer(client, inventory);
}

/**
 * @brief Pin command
 * @details Send the player inventory to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void pin(char **args, const client_t client,
    UNUSED const server_info_t serverInfo)
{
    int playerNumber;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: pin: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    playerNumber = atoi(args[1]);
    if (!is_number(args[1]) || playerNumber < 0) {
        printf("Client %d: pin: argument is not a valid number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_inventory(client, playerNumber);
}
