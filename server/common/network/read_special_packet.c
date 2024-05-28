/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** read_custom_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include "lib.h"

/**
 * @brief Get a thread from a packet
 * @details Get a thread from a packet
 *
 * @param packet the packet
 *
 * @return thread_t* the thread
 */
thread_t *get_thread_from_packet(packet_t *packet)
{
    thread_t *thread = my_malloc(THREAD_SIZE);

    memcpy(thread, packet->packet_body, THREAD_SIZE);
    return thread;
}

/**
 * @brief Get a team from a packet
 * @details Get a team from a packet
 *
 * @param packet the packet
 *
 * @return team_t* the team
 */
team_t *get_team_from_packet(packet_t *packet)
{
    team_t *team = my_malloc(TEAM_SIZE);

    memcpy(team, packet->packet_body, TEAM_SIZE);
    return team;
}

/**
 * @brief Get a reply from a packet
 * @details Get a reply from a packet
 *
 * @param packet the packet
 *
 * @return reply_t* the reply
 */
reply_t *get_reply_from_packet(packet_t *packet)
{
    reply_t *reply = my_malloc(REPLY_SIZE);

    memcpy(reply, packet->packet_body, REPLY_SIZE);
    return reply;
}

/**
 * @brief Get a channel from a packet
 * @details Get a channel from a packet
 *
 * @param packet the packet
 *
 * @return channel_t* the channel
 */
channel_t *get_channel_from_packet(packet_t *packet)
{
    channel_t *channel = my_malloc(CHANNEL_SIZE);

    memcpy(channel, packet->packet_body, CHANNEL_SIZE);
    return channel;
}

/**
 * @brief Get a message from a packet
 * @details Get a message from a packet
 *
 * @param packet the packet
 *
 * @return message_t* the message
 */
message_t *get_message_from_packet(packet_t *packet)
{
    message_t *message = my_malloc(MESSAGE_SIZE);

    memcpy(message, packet->packet_body, MESSAGE_SIZE);
    return message;
}
