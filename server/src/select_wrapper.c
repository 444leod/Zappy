/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** select_wrapper
*/

#include "zappy.h"
#include "clients.h"
#include "lib.h"
#include "macros.h"
#include "garbage_collector.h"
#include "debug.h"
#include "time_utils.h"
#include "select_wrapper.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/wait.h>

/**
 * @brief Add the clients to the write and read fd_sets
 * @details add the clients to the write and read fd_sets and update the
 *   max_sd variable, also update the fork status of the clients
 *
 * @param clients the clients to add to the fd_sets
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param max_sd the max_sd variable
*/
static void add_clients_to_set(client_list_t clients, select_data_t *sd)
{
    client_list_t client_node = clients;

    while (client_node) {
        if (client_node->client->packet_queue) {
            FD_SET(client_node->client->fd, sd->writefds);
            sd->max_sd = (client_node->client->fd > sd->max_sd) ?
                client_node->client->fd : sd->max_sd;
        }
        if (client_node->client->end || (client_node->client->type == AI &&
            get_list_size((node_t)client_node->client->commands) > 10)) {
            client_node = client_node->next;
            continue;
        }
        FD_SET(client_node->client->fd, sd->readfds);
        sd->max_sd = (client_node->client->fd > sd->max_sd) ?
            client_node->client->fd : sd->max_sd;
        client_node = client_node->next;
    }
}

/**
 * @brief Try to update the timeout with the
 *     command remaining time of the player
 * @details Try to update the timeout with the
 *    command remaining time of the player
 *
 * @param client the client to check
 * @param timeout the timeout to update
 */
static void try_command(client_t client, struct timeval **timeout)
{
    struct timeval tmp_timeout;

    if (!client->commands)
        return;
    tmp_timeout = get_timeval_by_double(
        client->commands->command->wait_duration);
    if ((*timeout)->tv_sec == -1) {
        **timeout = tmp_timeout;
        return;
    }
    tmp_timeout = get_timeval_by_double(
        client->commands->command->wait_duration);
    if (timevalcmp(&tmp_timeout, *timeout) < 0)
        **timeout = tmp_timeout;
}

/**
 * @brief Try to update the timeout with the
 *  death remaining time of the player
 * @details Try to update the timeout with the
 *  death remaining time of the player
 *
 * @param client the client to check
 * @param timeout the timeout to update
 */
static void try_death(const client_t client, struct timeval **timeout)
{
    struct timeval tmp_timeout;

    if (!client->player)
        return;
    tmp_timeout = get_timeval_by_double(client->player->death_remaining_time);
    if ((*timeout)->tv_sec == -1) {
        **timeout = tmp_timeout;
        return;
    }
    if (timevalcmp(&tmp_timeout, *timeout) < 0)
        **timeout = tmp_timeout;
}

/**
 * @brief Compare the timeval of the client (commands and death) and update
 * the timeout
 * @details Compare the timeval of the client (commands and death) and update
 * the timeout
 *
 * @param timeout the timeout to update
 * @param client the client to check
 *
 * @return true if the timeout has been updated with a packet_queue not empty
 * (special case), false otherwise
 */
static bool try_update_timeval(struct timeval **timeout, client_t client)
{
    if (client->end)
        return false;
    try_command(client, timeout);
    try_death(client, timeout);
    return false;
}

/**
 * @brief Get the timeout for the select function
 * @details Get the timeout for the select function by checking the
 *   clients commands and packet_queue
 *
 * @param clients the list of clients
 * @return struct timeval* the timeout
*/
static struct timeval *get_timeout(client_list_t clients,
    server_info_t serverInfo)
{
    client_list_t tmp = clients;
    struct timeval *timeout = NULL;

    timeout = my_malloc(sizeof(struct timeval));
    *timeout = get_timeval_by_double(serverInfo->refill_wait);
    DEBUG_PRINT("Refill: %ld %03ld\n", timeout->tv_sec, timeout->tv_usec);
    while (tmp) {
        if (try_update_timeval(&timeout, tmp->client))
            return timeout;
        tmp = tmp->next;
    }
    if (timeout->tv_sec == -1)
        return NULL;
    if (timeout->tv_sec < 0 || timeout->tv_usec < 0) {
        timeout->tv_sec = 0;
        timeout->tv_usec = 0;
    }
    return timeout;
}

/**
 * @brief Wrapper for the select function
 * @details wrapper for the select function, if the select function failed
 *   the program exit, else the function updates the fd_sets each 100ms.
 *
 * @param max_sd the max_sd variable
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param clients the list of clients
*/
void select_wrapper(select_data_t *sd, const client_list_t clients,
    const server_info_t serverInfo)
{
    struct timeval *timeout = get_timeout(clients, serverInfo);
    int activity = 0;

    add_clients_to_set(clients, sd);
    sd->max_sd++;
    special_print(sd->readfds, sd->writefds);
    DEBUG_PRINT("Timeout: %ld %03ld\n", timeout->tv_sec, timeout->tv_usec);
    activity = select(sd->max_sd, sd->readfds, sd->writefds, NULL, timeout);
    if (activity < 0)
        my_error("select wrapper failed");
    my_free(timeout);
}
