/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply_code
*/

#include "fcntl.h"
#include <stdio.h>
#include <stdbool.h>
#include "reply_code.h"
#include "clientllist.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief The server messages
 * @details The messages that the server can send to the client based on the
 * current code
*/
const server_message_t serverMessages[] = {
    {COMMAND_OK, "Command okay."},

    {GLOBAL_CONTEXT_SET, "Global context set."},
    {TEAM_CONTEXT_SET, "Team context set."},
    {CHANNEL_CONTEXT_SET, "Channel context set."},
    {THREAD_CONTEXT_SET, "Thread context set."},

    {NEW_USER, "Service ready for new user."},

    {SYNTAX_ERROR, "Syntax error, command unrecognized."},
    {SYNTAX_ERROR_IN_PARAMETERS,
        "Syntax error in parameters or arguments."},
    {COMMAND_NOT_IMPLEMENTED, "Command not implemented."},
    {BAD_COMMAND_SEQUENCE, "Bad sequence of commands."},
    {COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER,
        "Command not implemented for that parameter."},
    {NAME_TOO_LONG, "Name too long."},
    {DESCRIPTION_TOO_LONG, "Description too long."},
    {BODY_TOO_LONG, "Body too long."},
    {ALREADY_SUBSCRIBED, "Already subscribed."},
    {NOT_SUBSCRIBED, "You are not subscribed to this team."},
    {ALREADY_LOGGED_IN, "Already logged in."},
    {ALREADY_LOGGED_OUT, "Already logged out."},
    {ALREADY_EXISTS, "Already exists."},
    {UNSUFFICIENT_PERMISSIONS,
        "Unsufficient permissions to perform this action."},
    {NOT_LOGGED_IN, "Not logged in."},
    {USER_ALREADY_LOGGED_IN, "User already logged in."},

    {-1, "Something went wrong with the server (code rebuild missing)."}
};

/**
 * @brief Rebuild the packet with the current code
 * @details Rebuild the packet with the current code, using the serverMessages
 * list or the custom_messages_list
 * If it's a custom message, it will use the client buffer to send the message
 *
 * @param code the code to rebuild the packet with
 * @param packet the packet to rebuild
 *
 * @return the rebuilt packet
*/
packet_t *rebuild_packet(int code, packet_t *packet)
{
    uint16_t i = 0;
    enum PACKET_TYPE type = packet->packet_type;

    if (packet->packet_type != NONE && strlen(packet->packet_body) != 0)
        return packet;
    for (i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            my_free(packet);
            packet = build_custom_packet(code,
                my_strdup(serverMessages[i].message), type);
            return packet;
        }
    }
    return packet;
}

/**
 * @brief Reply to the client with the current code
 * @details Reply to the client with the current code
 *
 * @param client the client to reply to
*/
void reply_code(client_t client)
{
    packet_t *packet = pop_packet_from_queue(&client->packet_queue);
    int socketFd = client->fd;
    int code = packet->code;

    packet = rebuild_packet(code, packet);
    send_packet(socketFd, packet);
}
