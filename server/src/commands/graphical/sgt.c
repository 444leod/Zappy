/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sgt
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the time unit string
 *
 * @param server_info the server info
 * @return char* the time unit string
 */
char *get_time_unit_string(const server_info_t server_info)
{
    return my_snprintf("sgt %d", server_info->freq);
}

/**
 * @brief Send the time unit to a client
 *
 * @param client the client that executed the command
 * @param server_info the server info
 */
void send_time_unit_to_client(const client_t client,
    const server_info_t server_info)
{
    char *time_unit_string = get_time_unit_string(server_info);

    queue_buffer(client, time_unit_string);
    my_free(time_unit_string);
}

/**
 * @brief Send the time unit to all the clients in the list
 *
 * @param clients the list of clients
 * @param server_info the server info
 */
void send_time_unit_to_client_list(const client_list_t clients,
    const server_info_t server_info)
{
    char *time_unit_string = get_time_unit_string(server_info);
    client_list_t tmp = clients;

    while (tmp) {
        queue_buffer(tmp->client, time_unit_string);
        tmp = tmp->next;
    }
    my_free(time_unit_string);
}

/**
 * @brief SGT command
 * @details Send the time unit to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void sgt(char **args, const client_t client,
    const server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        queue_buffer(client, "sbp");
        printf("Client %d: sgt: bad argument number\n", client->fd);
        return;
    }
    send_time_unit_to_client(client, server_info);
}
