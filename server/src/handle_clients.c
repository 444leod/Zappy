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
}

/**
 * @brief Verify if the last message sent is a special case (EOF, error)
 * @details Verify if the last message sent is a special case (EOF, error)
 *
 * @param client the client to verify the special case of
 * @param valread the value read
 *
 * @return true if the last message sent is a special case, false otherwise
 * */
static bool is_read_special_case(const client_t client,
    const int valread)
{
    if (valread == -1) {
        remove_client(client->fd);
        client->fd = -1;
        printf("Read failed with fd %d: %s\n", client->fd, strerror(errno));
        return true;
    }
    if (valread == 0) {
        remove_client(client->fd);
        client->fd = -1;
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
static client_command_t create_command(const char *command,
    const struct timespec *time)
{
    client_command_t newCommand = my_malloc(sizeof(struct client_command_s));

    newCommand->command = my_strdup(command);
    newCommand->handledTime = *time;
    newCommand->initialized = false;
    return newCommand;
}

/**
 * @brief Clear the buffer overflow of an AI client
 * @details Clear the buffer overflow of an AI client (if the client has more
 * than 10 commands queued, new ones will be ignored)
 *
 * @param client the client to clear the buffer overflow of
*/
static void clear_ai_buffer_overflow(client_t client)
{
    uint32_t commandsSize = get_list_size((node_t)client->commands);

    if (commandsSize < 10)
        return;
    while (commandsSize > 10) {
        remove_from_list(get_node_by_index(11, (node_t)client->commands)->data,
            (node_t *)&client->commands);
        commandsSize--;
    }
}

/**
 * @brief Queue the next command of a client
 * @details Queue the next command of a client
 * if the client has a next command, queue it
 * if the client sent multiple commands, queue them into the next_commands
 *
 * @param client the client to queue the command of
*/
static void queue_command(const client_t client)
{
    char *afterLineBreak = NULL;
    int i = 0;
    struct timespec now;
    char *buffer = NULL;

    clock_gettime(0, &now);
    while (client->buffer && strlen(client->buffer) > 0) {
        afterLineBreak = strstr(client->buffer, "\n");
        if (!afterLineBreak)
            break;
        i = afterLineBreak - client->buffer;
        buffer = my_strndup(client->buffer, i);
        add_to_list((void *)create_command(buffer, &now),
            (void *)&client->commands);
        client->buffer = client->buffer + i + 1;
    }
    if (client->type == AI)
        clear_ai_buffer_overflow(client);
}

/**
 * @brief Read the buffer of a client
 *
 * @param client the client to read the buffer of
*/
static void read_buffer(const client_t client)
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
 * if the client is has command queued, handle the command
 * if the client is ready to write, send the buffer
 *
 * @param client the client to trigger the action of
 * @param readfds the readfds to check
 * @param writefds the writefds to check
 * @param serverInfo the serverInfo
*/
static void trigger_action(const client_t client, const fd_set *readfds,
    const fd_set *writefds, const server_info_t serverInfo)
{
    if (client->fd == -1)
        return;
    if (FD_ISSET(client->fd, readfds)) {
        read_buffer(client);
    }
    if (client->commands) {
        handle_command(client, serverInfo);
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
void loop_clients(const client_list_t clients, const fd_set *readfds,
    const fd_set *writefds, const server_info_t serverInfo)
{
    client_list_t clientNode = clients;
    int tempFd = 0;

    while (clientNode) {
        tempFd = clientNode->client->fd;
        if (clientNode->client->fd == -1) {
            clientNode = clientNode->next;
            continue;
        }
        trigger_action(clientNode->client, readfds, writefds, serverInfo);
        if (clientNode && clientNode->client &&
            clientNode->client->fd == tempFd)
            clientNode = clientNode->next;
    }
}
