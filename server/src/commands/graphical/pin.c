/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pin
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the player inventory string
 *
 * @param player the player
 * @return char* the player inventory string
 */
char *get_player_inventory_string(const player_t player)
{
    return my_snprintf("pin %d %d %d %d %d %d %d %d",
        player->player_number, player->food,
        player->rocks.linemate, player->rocks.deraumere,
        player->rocks.sibur, player->rocks.mendiane,
        player->rocks.phiras, player->rocks.thystame);
}

/**
 * @brief Send the player inventory to a client by the player_number
 * @details Send the player inventory to a client by the player_number
 *
 * @param client the client that executed the command
 * @param player_number the player number
*/
void send_player_inventory_to_client(const client_t client,
    const int player_number)
{
    player_t player = get_player_by_player_number(player_number);
    char *inventory;

    if (!player) {
        printf("Client %d: pin %d: player not found\n",
            client->fd, player_number);
        queue_buffer(client, "sbp");
        return;
    }
    inventory = get_player_inventory_string(player);
    queue_buffer(client, inventory);
    my_free(inventory);
}

/**
 * @brief Send the player inventory to a list of clients
 * @details Send the player inventory to a list of clients
 *
 * @param clients the list of clients
 * @param player_number the player number
 */
void send_player_inventory_to_client_list(const client_list_t clients,
    const int player_number)
{
    client_list_t tmp = clients;
    player_t player = get_player_by_player_number(player_number);
    char *inventory = "sbp";

    if (player)
        inventory = get_player_inventory_string(player);
    else
        printf("GLOBAL: pin %d: player not found\n", player_number);
    while (tmp) {
        queue_buffer(tmp->client, inventory);
        tmp = tmp->next;
    }
    if (player)
        my_free(inventory);
}

/**
 * @brief Pin command
 * @details Send the player inventory to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void pin(char **args, const client_t client,
    UNUSED const server_info_t server_info)
{
    int player_number;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: pin: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    player_number = atoi(args[1]);
    if (!is_number(args[1]) || player_number < 0) {
        printf("Client %d: pin: argument is not a valid number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_inventory_to_client(client, player_number);
}
