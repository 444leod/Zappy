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
 * @param player_id the player id
 */
void send_player_pos(const client_t client, const server_info_t server_info,
    const uint32_t player_id)
{
    client_list_t clients = *get_clients();
    player_t player = NULL;

    while (clients) {
        if (clients->client->player)
            player = clients->client->player;
        if (player->id == player_id) {
            queue_buffer(client, my_snprintf("ppo %d %d %d %d",
                player_id,
                player->position.x, player->position.y,
                player->orientation));
            return;
        }
        player = NULL;
    }
    printf("ppo %d: player not found\n", player_id);
    queue_buffer(client, "sbp");
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
    const server_info_t server_info)
{
    if (tablen((const void **)args) != 2) {
        queue_buffer(client, "sbp");
        return;
    }
    if (!is_number(args[1])) {
        queue_buffer(client, "sbp");
        return;
    }
    send_player_pos(client, server_info, atoi(args[1]));
}
