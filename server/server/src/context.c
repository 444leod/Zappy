/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** context
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "lib.h"

struct context_setup_s {
    int error_code;
    int error_type;
    void *(*checker)(unsigned char *);
};

static struct context_setup_s needed_setup[] = {
    {INEXISTANT_TEAM, TEAM, (void *(*)(uuid_t))get_team_by_uuid},
    {INEXISTANT_CHANNEL, CHANNEL, (void *(*)(uuid_t))get_channel_by_uuid},
    {INEXISTANT_THREAD, THREAD, (void *(*)(uuid_t))get_thread_by_uuid}
};

/**
 * @brief Check if the uuid is valid, readable and exists
 * @details Check if the uuid is valid, readable and exists
 *
 * @param client the client
 *
 * @return true if the uuids set are valid
 * @return false if the uuids set are not valid
 */
static bool are_uuid_valid(client_t client)
{
    char *uuids[4] = {client->team_uuid, client->channel_uuid,
        client->thread_uuid, NULL};
    uuid_t uuid;
    struct context_setup_s current_setup;

    for (int i = 0; i < tablen((void **)uuids); i++) {
        memset(uuid, 0, sizeof(uuid_t));
        current_setup = needed_setup[i];
        get_uuid_from_string(uuids[i], uuid);
        if (!is_uuid_valid(uuids[i]) || !current_setup.checker(uuid)) {
            add_packet_to_queue(&client->packet_queue,
                build_custom_packet(current_setup.error_code, uuids[i],
                    current_setup.error_type));
            return false;
        }
    }
    return true;
}

/**
 * @brief Check if the channel is related to the team
 * @details Check if the channel is related to the team
 *
 * @param client the client
 *
 * @return true if the channel is related to the team
 * @return false if the channel is not related to the team
 */
static bool check_channel_relation(client_t client)
{
    channel_t *channel;
    team_t *team;
    uuid_t channel_uuid;
    uuid_t team_uuid;

    get_uuid_from_string(client->channel_uuid, channel_uuid);
    get_uuid_from_string(client->team_uuid, team_uuid);
    channel = get_channel_by_uuid(channel_uuid);
    team = get_team_by_uuid(team_uuid);
    if (uuid_compare(channel->team_uuid, team->uuid) != 0) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_CHANNEL, client->channel_uuid,
                CHANNEL));
        return false;
    }
    return true;
}

/**
 * @brief Check if the thread is related to the channel
 * @details Check if the thread is related to the channel
 *
 * @param client the client
 *
 * @return true if the thread is related to the channel
 * @return false if the thread is not related to the channel
 */
static bool check_thread_relation(client_t client)
{
    thread_t *thread;
    channel_t *channel;
    uuid_t thread_uuid;
    uuid_t channel_uuid;

    get_uuid_from_string(client->thread_uuid, thread_uuid);
    get_uuid_from_string(client->channel_uuid, channel_uuid);
    thread = get_thread_by_uuid(thread_uuid);
    channel = get_channel_by_uuid(channel_uuid);
    if (uuid_compare(thread->channel_uuid, channel->uuid) != 0) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(INEXISTANT_THREAD, client->thread_uuid,
                THREAD));
        return false;
    }
    return true;
}

/**
 * @brief Check if the context uuids are related
 * @details Check if the context uuids are related (team -> channel -> thread)
 *
 * @param client the client
 *
 * @return true if the uuids are related
 * @return false if the uuids are not related
 */
static bool are_uuids_unrelated(client_t client)
{
    if (client->channel_uuid && !check_channel_relation(client))
        return false;
    if (client->thread_uuid && !check_thread_relation(client))
        return false;
    return true;
}

/**
 * @brief Check if the user can create something in the team set
 * @details Check if the user can create something in the team set
 *
 * @param client the client
 *
 * @return true if the user can create
 * @return false if the user can't create
 */
static bool can_user_create(client_t client)
{
    uuid_t team_uuid;

    get_uuid_from_string(client->team_uuid, team_uuid);
    if (!is_user_subscribed_to_team(client->user, team_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(NOT_SUBSCRIBED, client->team_uuid, TEAM));
        return false;
    }
    return true;
}

/**
 * @brief Return the current context of the client
 * @details Return the current context of the client
 *
 * @param client the client
 *
 * @return enum CONTEXT the current context
 */
enum CONTEXT get_current_context(client_t client)
{
    if (!client->team_uuid)
        return GLOBAL_CONTEXT;
    if (!client->channel_uuid)
        return TEAM_CONTEXT;
    if (!client->thread_uuid)
        return CHANNEL_CONTEXT;
    return THREAD_CONTEXT;
}

/**
 * @brief Check if the context is valid to do any action
 * @details Check if the context is valid to do any action
 *
 * @param client the client
 * @param need_subscription if the user needs to be subscribed to the team
 *
 * @return true if the context is valid
 * @return false if the context is not valid
 */
bool is_context_valid(client_t client, bool need_subscription)
{
    enum CONTEXT current_context = get_current_context(client);

    if (current_context == GLOBAL_CONTEXT)
        return true;
    if (!are_uuid_valid(client) || !are_uuids_unrelated(client))
        return false;
    if (need_subscription && current_context != GLOBAL_CONTEXT
        && !can_user_create(client))
        return false;
    return true;
}
