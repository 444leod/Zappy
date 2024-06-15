/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_death
*/

#include "game.h"
#include "time_utils.h"
#include "zappy.h"
#include "commands_utils.h"
#include <stdio.h>

/**
 * @brief Kill a player
 * @details Kill a player by removing it from map and queueing
 *  its death message
 *
 * @param client the client to kill
 * @param map the world map
 */
static void kill_player(const client_t client, const map_t map)
{
    printf("killing player with fd %d\n", client->fd);
    client->player->isDead = true;
    remove_player(client->player, map);
    queue_buffer(client, "dead");
    queue_to_graphical(get_player_death_string(client->player));
    printf("Player %d died.\n", client->player->playerNumber);
}

/**
 * @brief Check the status of a player by updating its death remaining time
 *  and kill it if needed
 * @details Check the status of a player by updating its death remaining time
 *  and kill it if needed
 *
 * @param client the client to update
 * @param server_info the server informations
 */
void check_player_death(const client_t client, const map_t map,
    const uint32_t frequency)
{
    if (!client->player || client->player->isDead)
        return;
    update_remaining_time(&client->player->death_remaining_time,
        &client->player->last_eat_check_time);
    if (client->player->death_remaining_time > 0) {
        return;
    }
    if (client->player->food > 0) {
        client->player->food--;
        client->player->death_remaining_time = DEATH_TICKS / frequency;
        return;
    }
    kill_player(client, map);
}
