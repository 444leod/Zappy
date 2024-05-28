/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** list
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
 * @brief Handle the team list
 * @details Handle the team list
 *
 * @param client the client
 */
static void handle_team_list(client_t client)
{
    packet_t *packet;
    teams_t *teams = get_teams();
    teams_t tmp = *teams;

    if (!tmp) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(EMPTY_TEAM_LIST, ""));
        return;
    }
    while (tmp) {
        packet = build_team_packet(TEAM_LIST, tmp->team);
        add_packet_to_queue(&client->packet_queue, packet);
        tmp = tmp->next;
    }
}

/**
 * @brief Handle the channel list
 * @details Handle the channel list
 *
 * @param client the client
 */
static void handle_channel_list(client_t client)
{
    packet_t *packet;
    channels_t channels;
    uuid_t team_uuid;

    get_uuid_from_string(client->team_uuid, team_uuid);
    channels = get_channels_by_team(team_uuid);
    if (!channels) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(EMPTY_CHANNEL_LIST, "", CHANNEL));
        return;
    }
    while (channels) {
        packet = build_channel_packet(CHANNEL_LIST, channels->channel);
        add_packet_to_queue(&client->packet_queue, packet);
        channels = channels->next;
    }
}

/**
 * @brief Handle the thread list
 * @details Handle the thread list
 *
 * @param client the client
 */
static void handle_thread_list(client_t client)
{
    packet_t *packet;
    threads_t threads;
    uuid_t channel_uuid;

    get_uuid_from_string(client->channel_uuid, channel_uuid);
    threads = get_threads_by_channel(channel_uuid);
    if (!threads) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(EMPTY_THREAD_LIST, "", THREAD));
        return;
    }
    while (threads) {
        packet = build_thread_packet(THREAD_LIST, threads->thread);
        add_packet_to_queue(&client->packet_queue, packet);
        threads = threads->next;
    }
}

/**
 * @brief Handle the reply list
 * @details Handle the reply list
 *
 * @param client the client
 */
static void handle_reply_list(client_t client)
{
    packet_t *packet;
    replies_t replies;
    uuid_t thread_uuid;

    get_uuid_from_string(client->thread_uuid, thread_uuid);
    replies = get_replies_by_thread(thread_uuid);
    if (!replies) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(EMPTY_REPLY_LIST, ""));
        return;
    }
    while (replies) {
        packet = build_reply_packet(REPLY_LIST, replies->reply);
        add_packet_to_queue(&client->packet_queue, packet);
        replies = replies->next;
    }
}

/**
 * @brief Handle the list command
 * @details Handle the list command
 *
 * @param client the client
 * @param command the command
 */
void list(client_t client, UNUSED char **command)
{
    enum CONTEXT context = get_current_context(client);

    if (!is_command_valid(client, command) || !is_context_valid(client, false))
        return;
    switch (context) {
        case GLOBAL_CONTEXT:
            handle_team_list(client);
            break;
        case TEAM_CONTEXT:
            handle_channel_list(client);
            break;
        case CHANNEL_CONTEXT:
            handle_thread_list(client);
            break;
        case THREAD_CONTEXT:
            handle_reply_list(client);
            break;
    }
}
