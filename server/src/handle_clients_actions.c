/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_clients
*/

#include "clients.h"
#include "zappy.h"
#include "commands.h"
#include "debug.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Send all the packets in the client's packet queue
 * @details Send all the packets in the client's packet queue
 *
 * @param client The client to send the packets
*/
static void send_buffer(client_t client)
{
    send_packets(client);
}

/**
 * @brief Trigger the action of a client based on its status
 * @details Trigger the action of a client based on its status
 * if the client is ready to read, read the buffer
 * if the client is has command queued, handle the command
 * if the client is ready to write, send the buffer
 *
 * @param client the client to trigger the action of
 * @param readfds the readfds to check
 * @param writefds the writefds to check
 * @param server_info the server_info
*/
static void trigger_action(const client_t client, const fd_set *readfds,
    const fd_set *writefds, const server_info_t server_info)
{
    check_player_death(client, server_info->map, server_info->freq);
    if (client->fd == -1)
        return;
    if (client->end && !client->packet_queue) {
        remove_client(client->fd);
        client->fd = -1;
    }
    if (FD_ISSET(client->fd, readfds)) {
        read_buffer(client);
    }
    if (client->commands) {
        handle_command(client, server_info);
    }
    if (FD_ISSET(client->fd, writefds) && client->packet_queue) {
        send_buffer(client);
    }
}

/**
 * @brief Loop through the clients and trigger their actions
 * @details Loop through the clients and trigger their actions
 *
 * @param clients the clients to loop through
 * @param readfds the readfds to check
 * @param writefds the writefds to check
 * @param server_info the server_info
*/
void loop_clients(const client_list_t clients, const fd_set *readfds,
    const fd_set *writefds, const server_info_t server_info)
{
    client_list_t client_node = clients;
    int tempFd = 0;

    while (client_node) {
        tempFd = client_node->client->fd;
        if (client_node->client->fd == -1) {
            client_node = client_node->next;
            continue;
        }
        trigger_action(client_node->client, readfds, writefds, server_info);
        if (client_node && client_node->client &&
            client_node->client->fd == tempFd)
            client_node = client_node->next;
    }
}
