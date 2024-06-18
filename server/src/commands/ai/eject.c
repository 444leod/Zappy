/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"
#include "garbage_collector.h"
#include "zappy.h"

/**
 * @brief Creates a packet formating the eject response
 * @param orientation The orientation the eject has been done at.
 * @return an allocated packet struct pointer (`packet_t *`).
 */
packet_t *get_eject_packet(enum ORIENTATION orientation)
{
    char *tmp = my_snprintf("eject: %d", (uint8_t)orientation);
    packet_t *packet = build_packet(tmp);

    my_free(tmp);
    return packet;
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
    position_t newPos = source->position;
    uint32_t size = get_list_size((node_t)others);
    player_list_t it = others;
    player_list_t next = NULL;
    packet_t *packet = NULL;

    newPos.y -= source->orientation == NORTH;
    newPos.y += source->orientation == SOUTH;
    newPos.x -= source->orientation == EAST;
    newPos.x += source->orientation == WEST;
    for (uint32_t i = 0; i < size; i++) {
        next = it->next;
        if (it->player != source) {
            packet = get_eject_packet(source->orientation);
            queue_packet_to_player(it->player, packet);
            move_player(it->player, newPos, map);
        }
        it = next;
    }
    return size > 1;
}

/**
 * @brief Destroy a list of eggs
 * @param eggs A pointer to the list of eggs to destroy
 */
void destroy_eggs(egg_list_t *eggs)
{
    egg_list_t node = *eggs;
    egg_list_t next = NULL;

    while (node) {
        next = node->next;
        node->egg->team->remainingSlots--;
        my_free(node->egg);
        my_free(node);
        node = next;
    }
    *eggs = NULL;
}

/**
 * @brief Eject command
 * @details Ejects all players from a tile and breaks eggs
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void eject(
    char **args,
    const client_t client,
    const server_info_t serverInfo)
{
    packet_t *packet = NULL;
    tile_t tile = NULL;
    bool ejected = false;

    if (tablen((const void **)args) != 1) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(client->player->position, serverInfo->map);
    ejected = eject_players(client->player, tile->players, serverInfo->map);
    packet = build_packet(ejected ? "ok" : "ko");
    destroy_eggs(&tile->eggs);
    add_packet_to_queue(&client->packetQueue, packet);
}
