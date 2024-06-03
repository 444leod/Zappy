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
 * @brief Execute the command
 * @details Execute the command of the client using the commands array
 *
 * @param command the command to execute;
 * @param client the client to execute the command for
*/
static void execute_command(client_command_t command, client_t client,
    server_info_t server_info)
{
    command->command_handler.func(command->args, client, server_info);
    remove_from_list((void *)command, (node_t *)&client->commands);
}

static bool should_be_handled(client_command_t command, client_t client)
{
    clock_t now;
    double time_elapsed;

    if (client->type == GRAPHICAL)
        return true;
    now = clock();
    time_elapsed = (double)(now - command->handled_at) / CLOCKS_PER_SEC * 10;
    return time_elapsed >= command->seconds_to_wait;
}

static void initialize_command(client_command_t command, client_t client,
    server_info_t server_info)
{
    size_t i = 0;

    command->initialized = true;
    command->args = str_to_word_array(command->command, " ");
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command->args[0]) == 0 &&
            commands[i].client_type == client->type) {
            command->command_handler = commands[i];
            command->seconds_to_wait = commands[i].wait_units == 0 ? 0 :
                commands[i].wait_units / server_info->freq;
            return;
        }
    }
    command->command_handler = commands[i];
    command->seconds_to_wait = 0;
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
*/
void handle_command(client_t client, server_info_t server_info)
{
    client_commands_t command_node = client->commands;

    if (command_node->command->initialized == false) {
        initialize_command(command_node->command, client, server_info);
    } else if (should_be_handled(command_node->command, client)) {
        execute_command(command_node->command, client, server_info);
    } else {
        DEBUG_PRINT("Command not ready to be handled\n");
    }
}
