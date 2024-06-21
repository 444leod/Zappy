/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include "commands.h"
#include "commands_utils.h"
#include "clients.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Gets the message argument in the boradcast command
 * Or throws NULL in case of errors with args
 * @param args The arguments
 * @return The message argument
 */
static const char *get_message(const char **args)
{
    int count = tablen((const void **)args);

    return (count != 2) ? NULL : args[1];
}

/**
 * @brief Adds a Subtracts two positions
 * @param a A pointer to a position that will be the result of the op
 * @param b The second position to add or sub
 * @param sub True to subtract, False to add.
 */
static void add_pos(position_t *a, position_t b, bool sub)
{
    a->x += b.x * (sub ? -1 : 1);
    a->y += b.y * (sub ? -1 : 1);
}

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
 * @brief Computes the position of a hearing square around a player
 * @param player The player
 * @param square The direction of the square
 * @return a global `position_t`
 */
position_t get_hearing_square(const player_t player, uint8_t square, map_t map)
{
    position_t pos = player->position;
    position_t fwd = {0, 0};
    position_t lft = {0, 0};

    get_relative_direction(player, &fwd, &lft);
    if (square < 3 || square > 7)
        add_pos(&pos, fwd, false);
    if (square >= 2 && square <= 4)
        add_pos(&pos, lft, false);
    if (square >= 4 && square <= 6)
        add_pos(&pos, fwd, true);
    if (square >= 6 && square <= 8)
        add_pos(&pos, lft, true);
    return (position_t){ pos.x % map->width, pos.y % map->height };
}

/**
 * @brief Computes the shortest path between two points on a torus map
 * @param a A first point
 * @param b A second point
 * @param map The map
 * @return The distance between the two points
 */
static uint32_t get_shortest_distance(position_t a, position_t b, map_t map)
{
    position_t diff = { abs(b.x - a.x), abs(b.y - a.y) };

    if (diff.x >= (int)map->width / 2)
        diff.x = map->width - diff.x;
    if (diff.y >= (int)map->height / 2)
        diff.y = map->height - diff.y;
    return diff.x * diff.x + diff.y * diff.y;
}

/**
 * @brief Computes the direction the broadcast arrived from
 * @param sender The position of the sender
 * @param receiver The receiving player
 * @return `uint8_t` designating the direction
 */
static uint8_t get_broadcast_source(
    position_t sender, const player_t receiver, map_t map)
{
    position_t square = {0, 0};
    uint32_t dist = 0;
    uint32_t closest = UINT32_MAX;
    uint8_t result = 0;

    for (uint8_t i = 1; i <= 8; i++) {
        square = get_hearing_square(receiver, i, map);
        dist = get_shortest_distance(square, sender, map);
        if (dist >= closest)
            continue;
        result = i;
        closest = dist;
    }
    return result;
}

/**
 * @brief Sends a message to all the AI clients with a player
 * @param source The source of the message
 * @param text The content of the message
 */
static void send_broadcast_to_clients(
    const player_t source, const char *text, map_t map)
{
    client_list_t *clients = get_clients();
    client_t client = NULL;
    uint8_t dir = 0;
    char *message = NULL;

    for (client_list_t node = *clients; node; node = node->next) {
        client = node->client;
        if (!client || !client->player || client->player == source)
            continue;
        dir = get_broadcast_source(source->position, client->player, map);
        message = my_snprintf("message %d, %s", dir, text);
        queue_buffer(client, message);
        my_free(message);
    }
}

/**
 * @brief Sends pbc #n M to graphical clients
 * @param player_number The player who sent broadcast
 * @param text The message content
 */
static void send_pbc(uint32_t player_number, const char *text)
{
    queue_to_graphical(my_snprintf("pbc %d %s", player_number, text));
}

/**
 * @brief Broadcast command
 * @details Tells a message to other players
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void broadcast(
    char **args,
    const client_t client,
    const server_info_t server_info)
{
    const char *message = get_message((const char **)args);

    if (message == NULL) {
        queue_buffer(client, "ko");
        return;
    }
    send_broadcast_to_clients(
        (const player_t)client->player, message, server_info->map);
    send_pbc(client->player->player_number, message);
    queue_buffer(client, "ok");
}
