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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/wait.h>

/**
 * @brief Get the timeval by a double
 * @details Get the timeval by a double
 *
 * @param waitDuration the double to convert to timeval
 *
 * @return struct timeval the timeval
 */
static struct timeval get_timeval_by_double(double waitDuration)
{
    struct timeval timeout;

    timeout.tv_sec = (time_t)waitDuration;
    timeout.tv_usec = (suseconds_t)((waitDuration - timeout.tv_sec) * 1e6);
    return timeout;
}

/**
 * @brief Compare two timeval
 * @details Compare two timeval
 *
 * @param a the first timeval
 * @param b the second timeval
 *
 * @return int the result of the comparison
 */
static int timevalcmp(struct timeval *a, struct timeval *b)
{
    if (a->tv_sec == b->tv_sec)
        return a->tv_usec - b->tv_usec;
    return a->tv_sec - b->tv_sec;
}

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
static void add_clients_to_set(
    client_list_t clients,
    fd_set *readfds,
    fd_set *writefds,
    int *max_sd)
{
    client_list_t clientNode = clients;

    while (clientNode) {
        if (clientNode->client->packetQueue)
            FD_SET(clientNode->client->fd, writefds);
        FD_SET(clientNode->client->fd, readfds);
        if (clientNode->client->fd > *max_sd)
            *max_sd = clientNode->client->fd;
        clientNode = clientNode->next;
    }
}

/**
 * @brief Compare the timeval of the command with the actual timeout, if the
 *  command has a lower timeout, update the timeout
 * @details Compare the timeval of the command with the actual timeout, if the
 * command has a lower timeout, update the timeout
 *
 * @param timeout the timeout to update
 * @param client the client to check
 *
 * @return true if the timeout has been updated with a packetQueue not empty
 * (special case), false otherwise
 */
static bool try_update_timeval(struct timeval *timeout, client_t client)
{
    double waitDuration;
    struct timeval tmp_timeout;

    if (client->packetQueue) {
        timeout->tv_sec = 0;
        timeout->tv_usec = 1;
        return true;
    }
    if (!client->commands)
        return false;
    waitDuration = client->commands->command->waitDuration;
    tmp_timeout = get_timeval_by_double(waitDuration);
    if (timevalcmp(&tmp_timeout, timeout) < 0) {
        timeout->tv_sec = tmp_timeout.tv_sec;
        timeout->tv_usec = tmp_timeout.tv_usec;
        return false;
    }
    return false;
}

/**
 * @brief Get the timeout for the select function
 * @details Get the timeout for the select function by checking the
 *   clients commands and packetQueue
 *
 * @param clients the list of clients
 * @return struct timeval* the timeout
*/
static struct timeval *get_timeout(client_list_t clients)
{
    client_list_t tmp = clients;
    struct timeval *timeout = my_malloc(sizeof(struct timeval));

    if (!tmp)
        return NULL;
    timeout->tv_sec = 10000000;
    timeout->tv_usec = 0;
    while (tmp) {
        if (try_update_timeval(timeout, tmp->client))
            return timeout;
        tmp = tmp->next;
    }
    if (timeout->tv_sec == 10000000 && timeout->tv_usec == 0)
        return NULL;
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
void select_wrapper(int *max_sd, fd_set *readfds,
    fd_set *writefds, client_list_t clients)
{
    struct timeval *timeout = get_timeout(clients);
    int activity = 0;

    add_clients_to_set(clients, readfds, writefds, max_sd);
    special_print(readfds, writefds);
    activity = select(*max_sd + 1, readfds, writefds, NULL, timeout);
    if (activity < 0)
        my_error("select wrapper failed");
}
