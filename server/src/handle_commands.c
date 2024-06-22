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
 * @param server_info the server info
*/
static void execute_command(const client_command_t command,
    const client_t client, const server_info_t server_info)
{
    if (client->type == AI) {
        DEBUG_PRINT("[DEBUG] Player %d executing command %s\n",
            client->fd, command->command);
    } else {
        DEBUG_PRINT("[DEBUG] Client %d executing command %s\n",
            client->fd, command->command);
    }
    command->command_handler.func(command->args, client, server_info);
    remove_from_list((void *)command, (node_t *)&client->commands);
}

/**
 * @brief Checks if the player IS STUNNED
 */
static bool check_player_stun(player_t player)
{
    struct timespec now;
    double elapsed_time;

    if (player->stun_time <= 0)
        return false;
    clock_gettime(0, &now);
    elapsed_time = (now.tv_sec - player->last_stuck_check.tv_sec);
    elapsed_time += (now.tv_nsec - player->last_stuck_check.tv_nsec)
        / 1000000000.0;
    player->stun_time -= elapsed_time;
    player->last_stuck_check = now;
    return player->stun_time >= 0;
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
    double elapsed_time;

    if (client->type != AI)
        return true;
    clock_gettime(0, &now);
    elapsed_time = (now.tv_sec - command->handled_time.tv_sec);
    elapsed_time += (now.tv_nsec - command->handled_time.tv_nsec)
        / 1000000000.0;
    command->handled_time = now;
    if (check_player_stun(client->player))
        return false;
    command->wait_duration -= elapsed_time;
    return command->wait_duration <= 0;
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
    command->args = parse_command_args(command->command);
    if (client->type == NONE) {
        command->command_handler = AUTHENTIFICATION_COMMAND;
        command->wait_duration = 0;
        return;
    }
    for (; COMMANDS[i].command; i++) {
        if (strcmp(COMMANDS[i].command, command->args[0]) == 0 &&
            COMMANDS[i].client_type == client->type) {
            command->command_handler = COMMANDS[i];
            command->wait_duration = COMMANDS[i].execution_ticks == 0 ? 0 :
                COMMANDS[i].execution_ticks / (double)server_info->freq;
            return;
        }
    }
    command->command_handler = COMMANDS[i];
    command->wait_duration = 0;
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
