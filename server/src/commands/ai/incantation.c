/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"
#include "zappy.h"
#include "time_utils.h"
#include <time.h>

/**
 * @brief 16-bit masks that determines the necessary
 * ressources for a incantation level.
 */
static const uint16_t incantation_masks[7] = {
    5120, 9536, 10312, 17796, 18032, 26308, 27305
};

/**
 * @brief Checks wethr a tile has necessary ressources for
 * a ritual at a given level
 *
 * @param level The ritual level
 * @param tile The tile the ritual is happening on
 * @return `true` if can start ritual, `false` otherwise.
 */
static bool check_tile_ressources(
    uint8_t level, player_list_t players, rocks_t rocks)
{
    uint16_t mask = 0;
    uint32_t count = get_list_size((node_t)players);

    if (level < 1 || level > 7)
        return false;
    mask = incantation_masks[level - 1];
    return (
        (mask >> 12 & 7) <= count &&
        (mask >> 10 & 3) <= rocks.linemate &&
        (mask >> 8 & 3) <= rocks.deraumere &&
        (mask >> 6 & 3) <= rocks.sibur &&
        (mask >> 4 & 3) <= rocks.mendiane &&
        (mask >> 2 & 3) <= rocks.phiras &&
        (mask >> 0 & 3) <= rocks.thystame
    );
}

/**
 * @brief Remove the rocks of a certain ritual level from the tile
 * @param level The ritual level
 * @param tile The tile
 */
static void consume_rocks(uint8_t level, tile_t tile)
{
    uint16_t mask = incantation_masks[level - 1];

    tile->rocks.linemate -= (mask >> 10 & 3);
    tile->rocks.deraumere -= (mask >> 8 & 3);
    tile->rocks.sibur -= (mask >> 6 & 3);
    tile->rocks.mendiane -= (mask >> 4 & 3);
    tile->rocks.phiras -= (mask >> 2 & 3);
    tile->rocks.thystame -= (mask >> 0 & 3);
}

/**
 * @brief Gets the players on a given tiles that are ready for incantation
 *
 * @param level The ritual level
 * @param tile The tile the ritual will happen on
 * @return a `player_list_t`.
 */
static player_list_t get_ready_players(uint8_t level, tile_t tile)
{
    player_list_t players = NULL;
    player_list_t node = tile->players;
    player_t tmp = NULL;

    while (node) {
        tmp = node->player;
        if (tmp->level == level && !tmp->ritual_id)
            add_to_list((void *)tmp, (node_t *)&players);
        node = node->next;
    }
    return players;
}

/**
 * @brief Gets the players that are doing a certain ritual by ID.
 *
 * @param level The ritual ID
 * @param tile The tile the ritual happened on
 * @return a `player_list_t`.
 */
static player_list_t get_ritual_players(uint32_t ritual, tile_t tile)
{
    player_list_t players = NULL;
    player_list_t node = tile->players;
    player_t tmp = NULL;

    while (node) {
        tmp = node->player;
        if (tmp->ritual_id == ritual)
            add_to_list((void *)tmp, (node_t *)&players);
        node = node->next;
    }
    return players;
}

/**
 * @brief Puts players in incantation state
 */
static void start_incantation(
    client_t client, player_list_t players, server_info_t server_info)
{
    packet_t *packet = NULL;
    uint32_t ritual = server_info->ritual_id + 1;
    struct timespec now = get_actual_time();

    server_info->ritual_id++;
    while (players) {
        packet = build_packet("Elevation underway");
        queue_packet_to_player(players->player, packet);
        players->player->ritual_id = ritual;
        if (players->player != client->player) {
            players->player->stun_time = 300.0 / (double)server_info->freq;
            players->player->last_stuck_check = now;
        }
        players = players->next;
    }
    prepend_client_command(client, create_command("EndIncantation", &now));
}

static void evolve(player_t player)
{
    char *msg = NULL;

    player->ritual_id = 0;
    player->level++;
    msg = my_snprintf("Current level: %d", player->level);
    queue_packet_to_player(player, build_packet(msg));
    my_free(msg);
}

/**
 * @brief Lets the player end an incantation ritual
 * @details starts an incantation.
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void end_incantation(
    UNUSED char **args,
    const client_t client,
    const server_info_t server_info)
{
    player_t player = client->player;
    tile_t tile = get_tile_at_position(player->position, server_info->map);
    player_list_t players = get_ritual_players(player->ritual_id, tile);
    uint8_t level = player->level;
    bool success = check_tile_ressources(level, players, tile->rocks);

    while (players) {
        if (success)
            evolve(players->player);
        else
            queue_packet_to_player(players->player, build_packet("ko"));
        players = players->next;
    }
    if (!success)
        return;
    consume_rocks(level, tile);
}

/**
 * @brief the Incantation command
 * @details starts an incantation.
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void incantation(
    char **args,
    const client_t client,
    const server_info_t server_info)
{
    player_list_t players = NULL;
    player_t player = client->player;
    tile_t tile = NULL;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(player->position, server_info->map);
    players = get_ready_players(player->level, tile);
    if (check_tile_ressources(player->level, players, tile->rocks))
        start_incantation(client, players, server_info);
    else
        throw_ko(client);
}
