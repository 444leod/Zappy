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
    uint32_t ready = 0;

    if (level < 1 || level > 7)
        return false;
    mask = incantation_masks[level - 1];
    ready = get_list_size((node_t)players);
    return (
        (mask >> 12 & 7) >= ready &&
        (mask >> 10 & 3) >= rocks.linemate &&
        (mask >> 8 & 3) >= rocks.deraumere &&
        (mask >> 6 & 3) >= rocks.sibur &&
        (mask >> 4 & 3) >= rocks.mendiane &&
        (mask >> 2 & 3) >= rocks.phiras &&
        (mask >> 0 & 3) >= rocks.thystame
    );
}

/**
 * @brief Gets the players on a given tiles that are ready for incantation
 * @return a `player_list_t`.
 */
static player_list_t get_ready_players(uint8_t level, tile_t tile)
{
    player_list_t players = NULL;
    player_list_t node = tile->players;
    player_t tmp = NULL;

    while (node) {
        tmp = node->player;
        if (tmp->level == level && !tmp->in_ritual)
            add_to_list((void *)tmp, (node_t *)&players);
        node = node->next;
    }
    return players;
}

/**
 * @brief Starts the ritual for every player
 * @param players The list of players that will start the ritual
 */
static void start_players_ritual(player_list_t players)
{
    client_command_t command = NULL;
    packet_t *packet = NULL;
    player_list_t node = players;

    while (node) {
        node->player->in_ritual = true;
        command = my_malloc(sizeof(client_command_t));
        command->command = my_strdup("DoElevation");
        packet = build_packet("Elevation underway");
        queue_packet_to_player(node->player, packet);
        prepend_player_command(node->player, command);
        node = node->next;
    }
}

/**
 * @brief the beginning of the Incantation command
 * @details Puts the player in an incantation state.
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void start_incantation(
    char **args,
    const client_t client,
    const server_info_t serverInfo)
{
    player_list_t players = NULL;
    player_t player = client->player;
    tile_t tile = NULL;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(player->position, serverInfo->map);
    players = get_ready_players(player->level, tile);
    if (check_tile_ressources(player->level, players, tile->rocks))
        start_players_ritual(players);
    else
        add_packet_to_queue(&client->packet_queue, build_packet("ko"));
}
