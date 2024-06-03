/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_clients
*/

#include "clients.h"
#include <sys/select.h>
#include "lib.h"
#include "zappy.h"
#include "commands.h"
#include "linked_lists.h"
#include "garbage_collector.h"
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
    if (client->packet_queue)
        send_packets(client);
}

/**
 * @brief Remove a client from the client list
 * @details Remove a client from the client list
 *
 * @param fd the fd of the client to remove
*/
static bool is_read_special_case(client_t client, int valread)
{
    if (valread == -1) {
        remove_client(client->fd);
        client->fd = -1;
        printf("Read failed with fd %d: %s\n", client->fd, strerror(errno));
        return true;
    }
    if (valread == 0) {
        remove_client(client->fd);
        return true;
    }
    return false;
}

/**
 * @brief Create a command
 * @details Create a command with the given command string and time
 *
 * @param command the command to create
 * @param time the time to create the command at
 *
 * @return the created command
*/
static client_command_t create_command(char *command, clock_t time)
{
    client_command_t new_command = my_malloc(sizeof(struct client_command_s));

    new_command->command = command;
    new_command->handled_at = time;
    new_command->initialized = false;
    return new_command;
}

/**
 * @brief Queue the next command of a client
 * @details Queue the next command of a client
 * if the client has a next command, queue it
 * if the client sent multiple commands, queue them into the next_commands
 *
 * @param client the client to queue the command of
*/
static void queue_command(client_t client)
{
    char *after_line_break = NULL;
    int i = 0;
    clock_t now = clock();

    if (client->type == AI && get_list_size((node_t)client->commands) == 10) {
        my_free(client->buffer);
        return;
    }
    while (client->buffer && strlen(client->buffer) > 0) {
        after_line_break = strstr(client->buffer, "\n");
        if (!after_line_break)
            break;
        i = after_line_break - client->buffer;
        add_to_list((void *)create_command(my_strndup(client->buffer, i), now),
            (void *)&client->commands);
        client->buffer = client->buffer + i + 1;
    }
    while (client->type == AI && get_list_size((node_t)client->commands) > 10)
        remove_from_list(get_node_by_index(11, (node_t)client->commands)->data,
            (node_t *)&client->commands);
}

/**
 * @brief Read the buffer of a client
 *
 * @param client the client to read the buffer of
*/
static void read_buffer(client_t client)
{
    char buffer[1025] = {0};
    int valread = 0;

    valread = read(client->fd, buffer, 1024);
    if (is_read_special_case(client, valread))
        return;
    buffer[valread] = '\0';
    if (valread > 0) {
        if (client->buffer && strlen(client->buffer) > 0)
            client->buffer = supercat(2, client->buffer, buffer);
        else
            client->buffer = my_strdup(buffer);
        queue_command(client);
    }
}

/**
 * @brief Trigger the action of a client based on its status
 * @details Trigger the action of a client based on its status
 * if the client is ready to read, read the buffer
 * if the client is ready to process, queue the command
 * if the client has a command, handle the command
 * if the client is ready to write, send the buffer
 *
 * @param client the client to trigger the action of
 * @param readfds the readfds to check
 * @param writefds the writefds to check
*/
static void trigger_action(client_t client, fd_set *readfds,
    fd_set *writefds, server_info_t server_info)
{
    if (client->fd == -1)
        return;
    if (FD_ISSET(client->fd, readfds))
        read_buffer(client);
    if (client->commands)
        handle_command(client, server_info);
    if (FD_ISSET(client->fd, writefds))
        send_buffer(client);
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
void loop_clients(client_t *clients, fd_set *readfds,
    fd_set *writefds, server_info_t server_info)
{
    client_t tmp = *clients;
    int tempFd = 0;

    while (tmp) {
        tempFd = tmp->fd;
        if (tmp->fd == -1) {
            tmp = tmp->next;
            continue;
        }
        trigger_action(tmp, readfds, writefds, server_info);
        if (tmp && tmp->fd == tempFd)
            tmp = tmp->next;
    }
}
