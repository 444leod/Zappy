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
 * @brief Send the correct reply code to the client
 * @details Send the correct reply code to the client
 * based on the current_code of the client
 * update the client status based on the next_commands
 *
 * @param client the client to send the reply code to
*/
static void send_buffer(client_t client)
{
    if (client->packetQueue)
        send_packets(client);
    if (client->player && client->player->isDead) {
        printf("Removing player fd %d\n", client->fd);
        remove_client(client->fd);
        client->fd = -1;
    }
}

/**
 * @brief Check if a client can interact
 * @details Check if a client can interact by checking if its a graphical
 *  client or if its player is not dead
 *
 * @param client the client to check
 *
 * @return true if the client can play, false otherwise
 */
static bool can_interact(client_t client)
{
    if (!client->player)
        return true;
    return !client->player->isDead;
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
 * @param serverInfo the serverInfo
*/
static void trigger_action(const client_t client, const fd_set *readfds,
    const fd_set *writefds, const server_info_t server_info)
{
    check_player_death(client, server_info->map, server_info->freq);
    if (client->fd == -1)
        return;
    if (FD_ISSET(client->fd, readfds) && can_interact(client)) {
        read_buffer(client);
    }
    if (client->commands && can_interact(client)) {
        handle_command(client, server_info);
    }
    if (FD_ISSET(client->fd, writefds)) {
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
 * @param serverInfo the serverInfo
*/
void loop_clients(const client_t *clients, const fd_set *readfds,
    const fd_set *writefds, const server_info_t serverInfo)
{
    client_t tmp = *clients;
    int tempFd = 0;

    while (tmp) {
        tempFd = tmp->fd;
        if (tmp->fd == -1) {
            tmp = tmp->next;
            continue;
        }
        trigger_action(tmp, readfds, writefds, serverInfo);
        if (tmp && tmp->fd == tempFd)
            tmp = tmp->next;
    }
}
