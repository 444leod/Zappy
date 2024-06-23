/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** mct
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"
#include "commands_utils.h"

/**
 * @brief Get the mct command full string
 * @details Get the mct command as a full string
 *
 * @param server_info the server info
 *
 * @return char * the map content string
 */
char *get_map_content_string(const server_info_t server_info)
{
    char *full_string = "";
    char *tile_content_string = "";

    for (uint32_t y = 0; y < server_info->height; y++) {
        for (uint32_t x = 0; x < server_info->width; x++) {
            tile_content_string = get_tile_content_string(
                get_tile_at_position((position_t){x, y}, server_info->map),
                (position_t){x, y});
            full_string = supercat(3, full_string, tile_content_string, "\n");
        }
    }
    return full_string;
}

/**
 * @brief Send the content of the map as bct command list to a client
 * @details Send the content of the map as bct command list to a client
 *
 * @param client the client
 * @param server_info the server infos
 */
void send_map_content_to_client(const client_t client,
    const server_info_t server_info)
{
    tile_t tile;
    position_t position = {0, 0};
    char *tile_content;

    for (uint32_t y = 0; y < server_info->height; y++) {
        for (uint32_t x = 0; x < server_info->width; x++) {
            position = (position_t){x, y};
            tile = get_tile_at_position(position, server_info->map);
            tile_content = get_tile_content_string(tile, position);
            queue_buffer(client, tile_content);
            my_free(tile_content);
        }
    }
}

/**
 * @brief Send the content of the map as bct command list to a client list
 * @details Send the content of the map as bct command list to a client list
 *
 * @param clients the client list
 * @param server_info the server infos
 */
void send_map_content_to_client_list(const client_list_t clients,
    const server_info_t server_info)
{
    client_list_t tmp = clients;
    position_t position = {0, 0};
    char *tile_content;

    for (; (uint32_t)position.y < server_info->height; position.x++) {
        if ((uint32_t)position.x == server_info->width) {
            position.x = 0;
            position.y++;
            continue;
        }
        tile_content = get_tile_content_string(
            get_tile_at_position(position, server_info->map), position);
        for (; tmp; tmp = tmp->next)
            queue_buffer(tmp->client, tile_content);
        my_free(tile_content);
        tmp = clients;
    }
}

/**
 * @brief Mct command
 * @details Send the map content to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void mct(char **args, const client_t client,
    const server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        return;
    }
    send_map_content_to_client(client, server_info);
}
