/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include "commands.h"
#include "commands_utils.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"
#include "garbage_collector.h"
#include "zappy.h"

/**
 * @brief Sets the forward and left relative direction of a player based on its
 * direction
 * @param player The player
 * @param forward A pointer to a position that will indicate a forward vector
 * @param left A pointer to a position that will indicate a left vector
 */
static void get_relative_direction(
    const player_t player, position_t *forward, position_t *left)
{
    if (player->orientation == NORTH) {
        *forward = (position_t){0, -1};
        *left = (position_t){-1, 0};
    }
    if (player->orientation == SOUTH) {
        *forward = (position_t){0, 1};
        *left = (position_t){1, 0};
    }
    if (player->orientation == EAST) {
        *forward = (position_t){1, 0};
        *left = (position_t){0, -1};
    }
    if (player->orientation == WEST) {
        *forward = (position_t){-1, 0};
        *left = (position_t){0, 1};
    }
}

/**
 * @brief Gets the number representing in which way they seem to be ejected
 * @param player the ejected player
 * @param move the ejection movement
 * @return uint8_t representing the direction
 */
static uint8_t get_eject_direction(player_t player, position_t move)
{
    position_t fwd = { 0, 0 };
    position_t lft = { 0, 0 };

    get_relative_direction(player, &fwd, &lft);
    if (move.x == fwd.x && move.y == fwd.y)
        return 5;
    if (move.x == -fwd.x && move.y == -fwd.y)
        return 1;
    if (move.x == lft.x && move.y == lft.y)
        return 7;
    if (move.x == -lft.x && move.y == -lft.y)
        return 3;
    return 0;
}

/**
 * @brief Creates a packet formating the eject response
 * @param orientation The orientation the eject has been done at.
 * @return an allocated packet struct pointer (`packet_t *`).
 */
static packet_t *get_eject_packet(player_t player, position_t offset)
{
    uint8_t dir = get_eject_direction(player, offset);
    char *tmp = my_snprintf("eject: %d", dir);
    packet_t *packet = build_packet(tmp);

    my_free(tmp);
    return packet;
}

/**
 * @brief Moves a player by a certain offset
 * @param player the player
 * @param offset The movement
 * @param map the map
 */
static void offset_player(player_t player, position_t offset, map_t map)
{
    position_t pos = {
        .x = player->position.x + offset.x,
        .y = player->position.y + offset.y,
    };

    move_player(player, pos, map);
}

/**
 * @brief Moves the players of a tile in the direction of a source player
 *
 * @param source The player that ejects the others
 * @param others The other players
 * @param map The map
 * @return `true` if a player was moved. `false` otherwise
 */
static bool eject_players(player_t source, player_list_t others, map_t map)
{
    position_t offset = {0, 0};
    player_list_t next = NULL;
    packet_t *packet = NULL;

    offset.y -= source->orientation == NORTH;
    offset.y += source->orientation == SOUTH;
    offset.x += source->orientation == EAST;
    offset.x -= source->orientation == WEST;
    for (player_list_t it = others; it; it = next) {
        next = it->next;
        if (it->player == source)
            continue;
        packet = get_eject_packet(it->player, offset);
        queue_packet_to_player(it->player, packet);
        offset_player(it->player, offset, map);
    }
    return (others != NULL);
}

/**
 * @brief Destroy a list of eggs
 * @param eggs A pointer to the list of eggs to destroy
 */
static void destroy_eggs(egg_list_t *eggs)
{
    egg_list_t node = *eggs;
    egg_list_t next = NULL;

    while (node) {
        next = node->next;
        queue_to_graphical(my_snprintf("edi %d", node->egg->number));
        node->egg->team->remaining_slots--;
        my_free(node->egg);
        my_free(node);
        node = next;
    }
    *eggs = NULL;
}

/**
 * @brief Sends the pex #n message to the graphical clients
 * @param player_number The player that did the ejection
 */
static void send_pex(uint16_t player_number)
{
    queue_to_graphical(my_snprintf("pex %d", player_number));
}

/**
 * @brief Eject command
 * @details Ejects all players from a tile and breaks eggs
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void eject(
    char **args,
    const client_t client,
    const server_info_t server_info)
{
    packet_t *packet = NULL;
    tile_t tile = NULL;
    bool ejected = false;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(client->player->position, server_info->map);
    ejected = eject_players(client->player, tile->players, server_info->map);
    packet = build_packet(ejected ? "ok" : "ko");
    if (ejected)
        send_pex(client->player->player_number);
    destroy_eggs(&tile->eggs);
    add_packet_to_queue(&client->packet_queue, packet);
}
