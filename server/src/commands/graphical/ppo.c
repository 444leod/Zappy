/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ppo
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the player position string
 *
 * @param player the player
 * @return char* the player position string
 */
char *get_player_pos_string(const player_t player)
{
    char orientation = get_char_by_orientation((int)player->orientation);

    return my_snprintf("ppo %d %d %d %c",
        player->player_number,
        player->position.x, player->position.y,
        orientation);
}

/**
 * @brief Send the player position to a client
 * @details Send the player position to a client
 *
 * @param client the client that executed the command
 * @param player_number the player number
 */
static void send_player_pos_to_client(const client_t client,
    const int player_number)
{
    player_t player = get_player_by_player_number(player_number);
    char *player_pos_string = "sbp";

    if (player)
        player_pos_string = get_player_pos_string(player);
    else
        printf("Client %d: ppo %d: player not found\n", client->fd,
            player_number);
    queue_buffer(client, player_pos_string);
    if (player)
        my_free(player_pos_string);
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
    int player_number;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: ppo: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    player_number = atoi(args[1]);
    if (!is_number(args[1]) || player_number < 0) {
        printf("Client %d: ppo: argument is not a number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_pos_to_client(client, player_number);
}
