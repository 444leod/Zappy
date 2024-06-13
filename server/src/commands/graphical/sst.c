/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sst
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the time unit modification string
 *
 * @param time_unit the time unit
 * @return char* the time unit modification string
 */
char *get_time_unit_modification_string(int time_unit)
{
    return my_snprintf("sst %d", time_unit);
}

/**
 * @brief Send the time unit modification to a client
 *
 * @param client the client that executed the command
 * @param time_unit the time unit
 */
void send_time_unit_modification_to_client(const client_t client,
    int time_unit)
{
    char *time_unit_string = get_time_unit_modification_string(time_unit);

    queue_buffer(client, time_unit_string);
    my_free(time_unit_string);
}

/**
 * @brief Send the time unit modification to all the clients in the list
 *
 * @param clients the list of clients
 * @param time_unit the time unit
 */
void send_time_unit_modification_to_client_list(const client_list_t clients,
    int time_unit)
{
    char *time_unit_string = get_time_unit_modification_string(time_unit);
    client_list_t tmp = clients;

    while (tmp) {
        queue_buffer(tmp->client, time_unit_string);
        tmp = tmp->next;
    }
    my_free(time_unit_string);
}

/**
 * @brief Sst command
 * @details Set the frequency of the server
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void sst(char **args, const client_t client,
    const server_info_t serverInfo)
{
    int time_unit = 0;

    if (tablen((const void **)args) != 2) {
        printf("Client %d: sst: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    time_unit = atoi(args[1]);
    if (!is_number(args[1]) || time_unit <= 0) {
        printf("Client %d: sst: argument is not a valid number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    serverInfo->freq = time_unit;
    send_time_unit_modification_to_client(client, time_unit);
}
