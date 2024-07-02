/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_buffer
*/

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include "clients.h"
#include "commands.h"
#include "linked_lists.h"
#include "garbage_collector.h"
#include "commands_utils.h"
#include "lib.h"

/**
 * @brief Create a command
 * @details Create a command with the given command string and time
 *
 * @param command the command to create
 * @param time the time to create the command at
 *
 * @return the created command
*/
client_command_t create_command(const char *command,
    const struct timespec *time)
{
    client_command_t new_command = my_malloc(sizeof(struct client_command_s));

    new_command->command = my_strdup(command);
    new_command->handled_time = *time;
    new_command->initialized = false;
    return new_command;
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
    uint32_t commands_size = get_list_size((node_t)client->commands);

    if (commands_size < 10)
        return;
    while (commands_size > 10) {
        remove_from_list(get_node_by_index(10, (node_t)client->commands)->data,
            (node_t *)&client->commands);
        commands_size--;
    }
}

static UNUSED void kill_player(client_t client)
{
    if (client->type == AI) {
        printf("Player %d died\n", client->player->player_number);
        queue_to_graphical(get_player_death_string(client->player));
        remove_from_list((void *)client,
            (node_t *)&client->player->team->players);
        client->fd = -1;
    }
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
    if (valread <= 0) {
        if (valread < 0)
            printf("Read failed with fd %d: %s\n",
                client->fd, strerror(errno));
        remove_client(client->fd);
        if (client->type == AI) {
            printf("Player %d died\n", client->player->player_number);
            queue_to_graphical(get_player_death_string(client->player));
            remove_from_list((void *)client,
                (node_t *)&client->player->team->players);
        client->fd = -1;
        }
        return true;
    }
    return false;
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
    char *after_line_break = NULL;
    int i = 0;
    struct timespec now;
    char *buffer = NULL;

    clock_gettime(0, &now);
    while (client->buffer && strlen(client->buffer) > 0) {
        after_line_break = strstr(client->buffer, "\n");
        if (!after_line_break && strlen(client->buffer) > 2048)
            my_free(client->buffer);
        if (!after_line_break)
            break;
        i = after_line_break - client->buffer;
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
void read_buffer(const client_t client)
{
    char buffer[1025] = {0};
    int valread = 0;

    if (client->type == AI && get_list_size((node_t)client->commands) >= 10)
        return;
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
