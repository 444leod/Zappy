/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** inventory
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Format the player inventory inside a string.
 * @details The inventory is presented as followed:
 * `[food 10, linemate 1, deraumere 0, ... ]`
 *
 * @param food The amount of food of the player
 * @param rocks The rocks structure of the player
 */
static char *format_inventory(uint32_t food, rocks_t rocks)
{
    char *str = NULL;

    str = my_snprintf(
        "[food %lu, linemate %lu, deraumere %lu, sibur %lu, " \
        "mendiane %lu, phiras %lu, thystame %lu]",
        food, rocks.linemate, rocks.deraumere, rocks.sibur,
        rocks.mendiane, rocks.phiras, rocks.thystame
    );
    return str;
}

/**
 * @brief Inventory command
 * @details Gets the player their inventory
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void inventory(char **args, client_t client, UNUSED server_info_t serverInfo)
{
    player_t player = client->player;
    char *inv = NULL;

    if (!assert_argv_count(args, 0)) {
        throw_ko(client);
        return;
    }
    inv = format_inventory(player->food, player->rocks);
    add_packet_to_queue(&client->packetQueue, build_packet(inv));
    my_free(inv);
}
