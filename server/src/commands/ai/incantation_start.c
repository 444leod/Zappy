/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation_start
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
 * @note They are stored in ascending order, first is the mask for leveling up
 * from level 1 to level 2, second is level 2 to 3, third for 3 to 4, etc...
 * @note Each value reprents the requirment to start or end an incantation
 * @note Every 2 bit starting from the end indicates an amount of rocks
 * @note The first bit is unused and the 3 bits after stands for player count
 */
static const uint16_t incantation_masks[7] = {
    0x1400, 0x2540, 0x2848, 0x4584, 0x4670, 0x66C4, 0x6AA9
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
        if (tmp->level == level && !tmp->ritual)
            add_to_list((void *)tmp, (node_t *)&players);
        node = node->next;
    }
    return players;
}

/**
 * @brief Creates a new incantation and add it to server list
 * @param players The list of players that do the incantation
 * @param server_info The server
 * @return incantation_t
 */
static incantation_t create_incantation(
    player_list_t players, server_info_t server_info)
{
    incantation_t ritual = NULL;

    if (!players)
        return NULL;
    ritual = my_malloc(sizeof(struct incantation_s));
    ritual->level = players->player->level;
    ritual->position = players->player->position;
    ritual->players = players;
    add_to_list((void *)ritual, (node_t *)&server_info->rituals);
    send_pic(ritual);
    return ritual;
}

/**
 * @brief Puts players in incantation state
 */
static void start_incantation(
    client_t client, player_list_t players, server_info_t server_info)
{
    packet_t *packet = NULL;
    incantation_t ritual = create_incantation(players, server_info);
    struct timespec now = get_actual_time();

    if (!ritual)
        return;
    while (players) {
        packet = build_packet("Elevation underway");
        queue_packet_to_player(players->player, packet);
        players->player->ritual = ritual;
        if (players->player != client->player) {
            players->player->stun_time = 300.0 / (double)server_info->freq;
            players->player->last_stuck_check = now;
        }
        players = players->next;
    }
    prepend_client_command(client, create_command("EndIncantation", &now));
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
