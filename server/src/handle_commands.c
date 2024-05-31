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
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Execute the command
 * @details Execute the command of the client using the commands array
 *
 * @param command the command to execute with its arguments
 * @param client the client to execute the command for
*/
static void execute_command(char **command, client_t client)
{
    size_t i = 0;

    DEBUG_PRINT("Executing command: %s\n", command[0]);
    if (command == NULL || command[0] == NULL) {
        unknown_command(client, command);
        return;
    }
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command);
            return;
        }
    }
    commands[i].func(client, command);
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
*/
void handle_command(client_t client)
{
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    DEBUG_PRINT("Handling command: %s\n", get_escaped_string(client->command));
    for (size_t i = 0; args && args[i]; i++)
        DEBUG_PRINT("Arg %ld: %s\n", i, get_escaped_string(args[i]));
    execute_command(args, client);
}
