/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** unknown_command
*/

#include "commands.h"
#include "reply_code.h"
#include "packet.h"

/**
 * @brief Function that handles unknown command
 * @details Function that handles unknown command, if the user is not logged in
 * it will return a NOT_LOGGED_IN packet,
 *  else it will return a SYNTAX_ERROR packet
 *
 * @param client the client
 * @param command the command
*/
void unknown_command(client_t client, UNUSED char **command)
{
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NOT_LOGGED_IN, ""));
    } else {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR, ""));
    }
}
