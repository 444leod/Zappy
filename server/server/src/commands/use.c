/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** use
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "lib.h"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

/**
 * @brief Check if the command is a special case
 * @details Check if the command is a special case, if so, handle it
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is a special case
 * @return false if the command is not a special case
 */
static bool is_special_case(client_t client, char **command)
{
    if (tablen((void **)command) == 1) {
        add_packet_to_queue(&client->packet_queue,
            build_packet(GLOBAL_CONTEXT_SET, ""));
        return true;
    }
    return false;
}

/**
 * @brief Check if the command is valid
 * @details Check if the command is valid
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is valid
 * @return false if the command is not valid
 */
static bool is_command_valid(client_t client, char **command)
{
    if (tablen((void **)command) > 4) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NOT_LOGGED_IN, ""));
        return false;
    }
    return true;
}

/**
 * @brief set the current client used items using the given uuids
 * @details set the current client used items using the given uuids
 *
 * @param client the client
 * @param command the command
 */
static int set_used_items(client_t client, char **command)
{
    int code[3] = {TEAM_CONTEXT_SET, CHANNEL_CONTEXT_SET, THREAD_CONTEXT_SET};

    switch (tablen((void **)command)) {
        case 4:
            client->thread_uuid = command[3];
        case 3:
            client->channel_uuid = command[2];
        case 2:
            client->team_uuid = command[1];
            break;
    }
    return code[tablen((void **)command) - 2];
}

/**
 * @brief /use command handler
 * @details /use command handler
 *
 * @param client the client
 * @param command the command
 */
void use(client_t client, char **command)
{
    int code = 0;

    if (!is_command_valid(client, command))
        return;
    client->team_uuid = NULL;
    client->channel_uuid = NULL;
    client->thread_uuid = NULL;
    if (is_special_case(client, command))
        return;
    code = set_used_items(client, command);
    add_packet_to_queue(&client->packet_queue, build_packet(code, ""));
}
