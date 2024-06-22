/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** plv
*/

#include "commands.h"
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
    return my_snprintf("plv %d %d", player->player_number, player->level);
}

/**
 * @brief Send the player level to a client
 * @details Send the player level to a client
 *
 * @param client the client that executed the command
 * @param player_number the player number
*/
static void send_player_level_to_client(const client_t client,
    const int player_number)
{
    player_t player = get_player_by_player_number(player_number);
    char *player_level_string;

    if (!player) {
        printf("Client %d: plv %d: player not found\n",
            client->fd, player_number);
        queue_buffer(client, "sbp");
        return;
    }
    player_level_string = get_player_level_string(player);
    queue_buffer(client, player_level_string);
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
    int player_number;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: plv: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    player_number = atoi(args[1]);
    if (!is_number(args[1]) || player_number < 0) {
        printf("Client %d: plv: argument is not a number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_player_level_to_client(client, player_number);
}
