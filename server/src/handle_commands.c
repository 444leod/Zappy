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
#include <time.h>

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
    if (client->type == AI) {
        DEBUG_PRINT("[DEBUG] Player %d executing command %s\n",
            client->fd, command->command);
    } else {
        DEBUG_PRINT("[DEBUG] Client %d executing command %s\n",
            client->fd, command->command);
    }
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
    struct timespec now;
    double elapsedTime;

    if (client->type == GRAPHICAL)
        return true;
    clock_gettime(0, &now);
    elapsedTime = (now.tv_sec - command->handledTime.tv_sec);
    elapsedTime += (now.tv_nsec - command->handledTime.tv_nsec) / 1000000000.0;
    command->waitDuration -= elapsedTime;
    command->handledTime = now;
    return command->waitDuration <= 0;
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
    }
}
