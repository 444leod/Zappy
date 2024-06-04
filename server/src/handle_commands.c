/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_commands
*/

#include "clients.h"
#include <sys/select.h>
#include "commands.h"
#include "lib.h"
#include "zappy.h"
#include "debug.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Execute the given command
 * @details Execute the given command
 *
 * @param command the command to execute;
 * @param client the client to execute the command for
 * @param server_info the server info
*/
static void execute_command(const client_command_t command,
    const client_t client, const server_info_t server_info)
{
    command->command_handler.func(command->args, client, server_info);
    remove_from_list((void *)command, (node_t *)&client->commands);
}

/**
 * @brief Check if the command should be handled
 * @details Check if the command should be handled
 *      by checking if the time elapsed since the last time the command was
 *      handled is greater than the time to wait or if the client is graphical
 *      (no time to wait for graphical clients)
 *
 * @param command the command to check
 * @param client the client to check the command for
 *
 * @return true if the command should be handled, false otherwise
*/
static bool should_be_handled(const client_command_t command,
    const client_t client)
{
    clock_t now;
    double time_elapsed;

    if (client->type == GRAPHICAL)
        return true;
    now = clock();
    time_elapsed = (double)(now - command->handled_at) / CLOCKS_PER_SEC * 10;
    return time_elapsed >= command->seconds_to_wait;
}

/**
 * @brief Initialize the command
 * @details Initialize the command by parsing it and setting the
 *  command_handler and seconds_to_wait
 *
 * @param command the command to initialize
 * @param client the client to initialize the command for
 * @param server_info the server info
*/
static void initialize_command(const client_command_t command,
    const client_t client, const server_info_t server_info)
{
    size_t i = 0;

    command->initialized = true;
    command->args = str_to_word_array(command->command, " ");
    for (; COMMANDS[i].command; i++) {
        if (strcmp(COMMANDS[i].command, command->args[0]) == 0 &&
            COMMANDS[i].client_type == client->type) {
            command->command_handler = COMMANDS[i];
            command->seconds_to_wait = COMMANDS[i].wait_units == 0 ? 0 :
                COMMANDS[i].wait_units / server_info->freq;
            return;
        }
    }
    command->command_handler = COMMANDS[i];
    command->seconds_to_wait = 0;
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
 * @param server_info the server info
*/
void handle_command(const client_t client, const server_info_t server_info)
{
    const client_command_list_t command_node = client->commands;

    if (command_node->command->initialized == false) {
        initialize_command(command_node->command, client, server_info);
    } else if (should_be_handled(command_node->command, client)) {
        execute_command(command_node->command, client, server_info);
    } else {
        DEBUG_PRINT("Command not ready to be handled\n");
    }
}
