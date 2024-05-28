/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** info
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

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
    if (tablen((void **)command) > 1) {
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
 * @brief Handle the user info
 * @details Handle the user info
 *
 * @param client the client
 */
static void handle_user_info(client_t client)
{
    packet_t *packet = build_userinfo_packet(USER_INFO, client->user->username,
        client->user->uuid, client->user->status);

    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the team info
 * @details Handle the team info
 *
 * @param client the client
 */
static void handle_team_info(client_t client)
{
    team_t *team;
    uuid_t team_uuid;
    packet_t *packet;

    get_uuid_from_string(client->team_uuid, team_uuid);
    team = get_team_by_uuid(team_uuid);
    packet = build_team_packet(TEAM_INFO, team);
    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the channel info
 * @details Handle the channel info
 *
 * @param client the client
 */
static void handle_channel_info(client_t client)
{
    channel_t *channel;
    uuid_t channel_uuid;
    packet_t *packet;

    get_uuid_from_string(client->channel_uuid, channel_uuid);
    channel = get_channel_by_uuid(channel_uuid);
    packet = build_channel_packet(CHANNEL_INFO, channel);
    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the thread info
 * @details Handle the thread info
 *
 * @param client the client
 */
static void handle_thread_info(client_t client)
{
    thread_t *thread;
    uuid_t thread_uuid;
    packet_t *packet;

    get_uuid_from_string(client->thread_uuid, thread_uuid);
    thread = get_thread_by_uuid(thread_uuid);
    packet = build_thread_packet(THREAD_INFO, thread);
    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the info command
 * @details Handle the info command
 *
 * @param client the client
 * @param command the command
 */
void info(client_t client, UNUSED char **command)
{
    enum CONTEXT context = get_current_context(client);

    if (!is_command_valid(client, command) || !is_context_valid(client, false))
        return;
    switch (context) {
        case GLOBAL_CONTEXT:
            handle_user_info(client);
            break;
        case TEAM_CONTEXT:
            handle_team_info(client);
            break;
        case CHANNEL_CONTEXT:
            handle_channel_info(client);
            break;
        case THREAD_CONTEXT:
            handle_thread_info(client);
            break;
    }
}
