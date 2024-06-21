/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include "commands.h"
#include "commands_utils.h"
#include "lib.h"
#include "zappy.h"
#include "time_utils.h"

/**
 * @brief End of Fork command
 * @details Creates an egg at player's feet
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void end_fork(
    UNUSED char **args,
    const client_t client,
    const server_info_t server_info)
{
    player_t player = client->player;
    egg_t egg = add_egg_at_position(
        client->player->team, client->player->position, server_info->map);
    char *msg = NULL;

    client->player->team->remaining_slots++;
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
    msg = my_snprintf("enw %d %d %d %d",
        egg->number, player->player_number,
        player->position.x, player->position.y);
    queue_to_graphical(msg);
}

/**
 * @brief Fork command
 * @details Buffers end of fork command
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void fork_player(
    char **args,
    const client_t client,
    UNUSED const server_info_t server_info)
{
    struct timespec now = get_actual_time();

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    prepend_client_command(client, create_command("EndFork", &now));
    queue_to_graphical(my_snprintf("pfk %d", client->player->player_number));
}
