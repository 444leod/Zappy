/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

struct parameters {
    enum CONTEXT context;
    size_t needed_len;
    size_t first_param_max_len;
    size_t second_param_max_len;
};

static struct parameters parameters[4] = {
    {GLOBAL_CONTEXT, 3, MAX_NAME_LENGTH, MAX_DESCRIPTION_LENGTH},
    {TEAM_CONTEXT, 3, MAX_NAME_LENGTH, MAX_DESCRIPTION_LENGTH},
    {CHANNEL_CONTEXT, 3, MAX_NAME_LENGTH, MAX_BODY_LENGTH},
    {THREAD_CONTEXT, 2, MAX_BODY_LENGTH, 0}
};

/**
 * @brief Send the given packet to all the logged subscribers of the team
 * @details Send the given packet to all the logged subscribers of the team
 *        except the current client
 * @param team_uuid the team uuid
 * @param packet the packet
 * @param current_client the current client
*/
static void send_to_logged_subscribers(
    uuid_t team_uuid,
    packet_t *packet,
    client_t current_client)
{
    clients_t clients;
    team_t *team = get_team_by_uuid(team_uuid);
    users_t subscribers = get_team_subscribers(team);
    user_t user;

    while (subscribers) {
        user = get_user_by_uuid(subscribers->user->user_uuid);
        if (subscribers->user->is_logged) {
            clients = get_clients_by_user(user, current_client);
            send_packet_to_clients(clients, packet);
        }
        subscribers = subscribers->next;
    }
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
    int command_len = tablen((void **)command);

    if (command_len != 2 && command_len != 3) {
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
 * @brief Check if the arguments are correct for the given context
 * @details Check if the arguments are correct for the given context
 *
 * @param client the client
 * @param command the command
 * @param context the context
 *
 * @return true if the arguments are correct
 * @return false if the arguments are not correct
 */
static bool are_arguments_correct(client_t client, char **command,
    enum CONTEXT context)
{
    size_t command_len = tablen((void **)command);
    struct parameters params = parameters[context];

    if (command_len != params.needed_len) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (strlen(command[1]) > params.first_param_max_len) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NAME_TOO_LONG, ""));
        return false;
    }
    if (params.second_param_max_len != 0 &&
        strlen(command[2]) > params.second_param_max_len) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(BODY_TOO_LONG, ""));
        return false;
    }
    return true;
}

/**
 * @brief handle the create team context
 * @details handle the create team context
 *
 * @param client the client
 * @param command the command
*/
static void handle_team_creation(client_t client, char **command)
{
    char *team_name = command[1];
    char *team_description = command[2];
    team_t *team;
    packet_t *packet;

    if (get_team_by_name(team_name)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(ALREADY_EXISTS, "", TEAM));
        return;
    }
    team = create_team(team_name, team_description, client->user->uuid);
    packet = build_team_packet(TEAM_CREATED, team);
    add_packet_to_queue(&client->packet_queue, packet);
    send_packet_to_logged_users(packet, client);
}

/**
 * @brief handle the create channel context
 * @details handle the create channel context
 *
 * @param client the client
 * @param command the command
*/
static void handle_channel_creation(client_t client, char **command)
{
    char *name = command[1];
    char *description = command[2];
    channel_t *channel;
    packet_t *packet;
    uuid_t team_uuid;

    get_uuid_from_string(client->team_uuid, team_uuid);
    if (get_channel_by_name_by_team_uuid(name, team_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(ALREADY_EXISTS, "", CHANNEL));
        return;
    }
    channel = create_channel(name, description, team_uuid);
    packet = build_channel_packet(CHANNEL_CREATED, channel);
    add_packet_to_queue(&client->packet_queue, packet);
    send_to_logged_subscribers(team_uuid, packet, client);
}

/**
 * @brief handle the create thread context
 * @details handle the create thread context
 *
 * @param client the client
 * @param command the command
*/
static void handle_thread_creation(client_t client, char **command)
{
    char *title = command[1];
    char *body = command[2];
    packet_t *packet;
    thread_t *thread;
    uuid_t team_uuid;
    uuid_t channel_uuid;

    get_uuid_from_string(client->team_uuid, team_uuid);
    get_uuid_from_string(client->channel_uuid, channel_uuid);
    if (get_thread_by_title_by_channel_uuid(title, channel_uuid)) {
        add_packet_to_queue(&client->packet_queue,
            build_custom_packet(ALREADY_EXISTS, "", THREAD));
        return;
    }
    thread = create_thread(title, body, client->user->uuid, channel_uuid);
    packet = build_thread_packet(THREAD_CREATED, thread);
    add_packet_to_queue(&client->packet_queue, packet);
    send_to_logged_subscribers(team_uuid, packet, client);
}

/**
 * @brief handle the reply team context
 * @details handle the reply team context
 *
 * @param client the client
 * @param command the command
*/
static void handle_reply_creation(client_t client, char **command)
{
    char *reply_body = command[1];
    packet_t *packet;
    reply_t *reply;
    uuid_t thread_uuid;
    uuid_t team_uuid;

    get_uuid_from_string(client->thread_uuid, thread_uuid);
    get_uuid_from_string(client->team_uuid, team_uuid);
    reply = create_reply(reply_body, client->user->uuid, thread_uuid);
    packet = build_reply_packet(REPLY_CREATED, reply);
    add_packet_to_queue(&client->packet_queue, packet);
    send_to_logged_subscribers(team_uuid, packet, client);
}

/**
 * @brief Create command handler. Create either a team, a channel, a thread
 *      or a reply, based on the current context
 * @details Create either a team, a channel, a thread or a reply, based on the
 *     current context
 *
 * @param client the client
 * @param command the command
 */
void create(client_t client, char **command)
{
    enum CONTEXT context = get_current_context(client);

    if (!is_command_valid(client, command) || !is_context_valid(client, true))
        return;
    if (!are_arguments_correct(client, command, context))
        return;
    switch (context) {
        case GLOBAL_CONTEXT:
            handle_team_creation(client, command);
            break;
        case TEAM_CONTEXT:
            handle_channel_creation(client, command);
            break;
        case CHANNEL_CONTEXT:
            handle_thread_creation(client, command);
            break;
        case THREAD_CONTEXT:
            handle_reply_creation(client, command);
            break;
    }
}
