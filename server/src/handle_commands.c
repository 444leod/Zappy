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
 * @param serverInfo the server info
*/
static void execute_command(const client_command_t command,
    const client_t client, const server_info_t serverInfo)
{
    command->commandHandler.func(command->args, client, serverInfo);
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
    double elapsedTime;

    if (client->type == GRAPHICAL)
        return true;
    now = clock();
    elapsedTime = (double)(now - command->handledTime) / CLOCKS_PER_SEC * 10;
    return elapsedTime >= command->waitDuration;
}

/**
 * @brief Initialize the command
 * @details Initialize the command by parsing it and setting the
 *  command_handler and seconds_to_wait
 *
 * @param command the command to initialize
 * @param client the client to initialize the command for
 * @param serverInfo the server info
*/
static void initialize_command(const client_command_t command,
    const client_t client, const server_info_t serverInfo)
{
    size_t i = 0;

    command->initialized = true;
    command->args = str_to_word_array(command->command, " ");
    if (client->type == NONE) {
        command->commandHandler = AUTHENTIFICATION_COMMAND;
        command->waitDuration = 0;
        return;
    }
    for (; COMMANDS[i].command; i++) {
        if (strcmp(COMMANDS[i].command, command->args[0]) == 0 &&
            COMMANDS[i].ClientType == client->type) {
            command->commandHandler = COMMANDS[i];
            command->waitDuration = COMMANDS[i].waitUnits == 0 ? 0 :
                COMMANDS[i].waitUnits / serverInfo->freq;
            return;
        }
    }
    command->commandHandler = COMMANDS[i];
    command->waitDuration = 0;
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
 * @param serverInfo the server info
*/
void handle_command(const client_t client, const server_info_t serverInfo)
{
    const client_command_list_t commandNode = client->commands;

    if (commandNode->command->initialized == false) {
        initialize_command(commandNode->command, client, serverInfo);
    } else if (should_be_handled(commandNode->command, client)) {
        execute_command(commandNode->command, client, serverInfo);
    } else {
        DEBUG_PRINT("Command not ready to be handled\n");
    }
}
