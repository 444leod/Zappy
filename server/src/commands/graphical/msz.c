/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** msz
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the map size string
 *
 * @param server_info the server info
 * @return char* the map size string
 */
char *get_map_size_string(const server_info_t server_info)
{
    return my_snprintf("msz %d %d", server_info->width,
        server_info->height);
}

/**
 * @brief Send the map size to a client
 *
 * @param client the client
 * @param server_info the server info
 */
static void send_map_size_to_client(const client_t client,
    const server_info_t server_info)
{
    char *map_size_string = get_map_size_string(server_info);

    queue_buffer(client, map_size_string);
    my_free(map_size_string);
}

/**
 * @brief Msz command
 * @details Send the map size to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void msz(char **args, client_t client,
    server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        return;
    }
    send_map_size_to_client(client, server_info);
}
