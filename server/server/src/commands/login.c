/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** login
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"

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
    if (tablen((void **)command) != 2) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (strlen(command[1]) > 32) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NAME_TOO_LONG, ""));
        return false;
    }
    return true;
}

/**
 * @brief Create a user
 * @details Create a user with the given username
 *
 * @param username the username
 * @param code the code
 *
 * @return the created user
 */
user_t create_user(char *username)
{
    user_t new_user;
    char *username_buffer = my_malloc(sizeof(char) * MAX_NAME_LENGTH + 1);
    char *uuid_string;

    memset(username_buffer, 0, sizeof(char) * MAX_NAME_LENGTH + 1);
    add_user_by_username(username);
    new_user = get_user_by_username(username);
    memcpy(username_buffer, new_user->username, MAX_NAME_LENGTH + 1);
    uuid_string = get_uuid_as_string(new_user->uuid);
    server_event_user_created(uuid_string, username_buffer);
    return new_user;
}

/**
 * @brief Check if the user is already logged, if so, handle it.
 * @details Check if the user is already logged, if so, handle it.
 *
 * @param client the client
 * @param user the user
 *
 * @return true if the user is already logged and the case has been handled
 * @return false if the user is not already logged
 */
static bool is_already_logged_case(client_t client, user_t user)
{
    packet_t *packet;

    if (client->user == NULL)
        return false;
    packet = build_userinfo_packet(USER_LOGGED_OUT, client->user->username,
        client->user->uuid, client->user->status);
    server_event_user_logged_out(get_uuid_as_string(client->user->uuid));
    send_packet_to_logged_users(packet, NULL);
    if (user == NULL)
        return false;
    if (get_clients_by_user(client->user, client) == NULL)
        client->user->status = STATUS_NOT_LOGGED_IN;
    client->user = user;
    user->status = STATUS_LOGGED_IN;
    packet = build_userinfo_packet(USER_LOGGED_IN,
        user->username, user->uuid, user->status);
    add_packet_to_queue(&client->packet_queue, packet);
    server_event_user_logged_in(get_uuid_as_string(user->uuid));
    send_packet_to_logged_users(packet, client);
    return true;
}

/**
 * @brief Login command handler. Login a user with the given username
 * @details Login a user with the given username
 *
 * @param client the client
 * @param command the command
 */
void login(client_t client, char **command)
{
    user_t user;
    packet_t *packet;

    if (!is_command_valid(client, command))
        return;
    user = get_user_by_username(command[1]);
    if (is_already_logged_case(client, user))
        return;
    if (!user)
        user = create_user(command[1]);
    client->user = user;
    user->status = STATUS_LOGGED_IN;
    packet = build_userinfo_packet(USER_LOGGED_IN,
        user->username, user->uuid, user->status);
    add_packet_to_queue(&client->packet_queue, packet);
    server_event_user_logged_in(get_uuid_as_string(user->uuid));
    send_packet_to_logged_users(packet, client);
}
