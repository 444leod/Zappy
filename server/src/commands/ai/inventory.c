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

static char *cleancat(char *a, char *b)
{
    char *result = supercat(2, a, b);

    free(a);
    free(b);
    return result;
}

static char *add_rock(char *str, const char *rock, uint32_t n)
{
    char *frock = NULL;
    char *result = NULL;

    if (n <= 0)
        return str;
    frock = my_snprintf("%s %d", rock, n);
    result = supercat(3, str, (str[1] ? "," : ""), frock);
    my_free(str);
    my_free(frock);
    return result;
}

static char *format_inventory(rocks_t rocks)
{
    char *str = my_strdup("[");

    if (rocks.linemate > 0)
        str = add_rock(str, "linemate", rocks.linemate);
    if (rocks.deraumere > 0)
        str = add_rock(str, "deraumere", rocks.deraumere);
    if (rocks.sibur > 0)
        str = add_rock(str, "sibur", rocks.sibur);
    if (rocks.mendiane > 0)
        str = add_rock(str, "mendiane", rocks.mendiane);
    if (rocks.phiras > 0)
        str = add_rock(str, "phiras", rocks.phiras);
    if (rocks.thystame > 0)
        str = add_rock(str, "thystame", rocks.thystame);
    return cleancat(str, my_strdup("]"));
}

/**
 * @brief Inventory command
 * @details Gets the player their inventory
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server info
 */
void inventory(UNUSED char **args, client_t client,
    UNUSED server_info_t serverInfo)
{
    char *inv = format_inventory(client->player->rocks);
    packet_t *packet = build_packet(inv);

    my_free(inv);
    add_packet_to_queue(&client->packetQueue, packet);
}
