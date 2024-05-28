/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** build_custom_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include <unistd.h>
#include <string.h>

/**
 * @brief Build a packet with a code and a thread
 * @details Build a packet with the given code and thread, its type is set to
 *        THREAD
 *
 * @param code the code
 * @param thread the thread
 *
 * @return the created packet
*/
packet_t *build_thread_packet(int code, thread_t *thread)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = THREAD;
    packet->is_global = false;
    memcpy(packet->packet_body, thread, THREAD_SIZE);
    return packet;
}

/**
 * @brief Build a packet with a code and a team informations
 * @details Build a packet with the given code and team, its type is set to
 *        TEAM
 *
 * @param code the code
 * @param title the title
 * @param description the description
 * @param creator_uuid the creator_uuid
 *
 * @return the created packet
*/
packet_t *build_team_packet(int code, team_t *team)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = TEAM;
    packet->is_global = false;
    memcpy(packet->packet_body, team, TEAM_SIZE);
    return packet;
}

/**
 * @brief Build a reply packet with a code and reply informations
 * @details Build a packet with the given code and reply info,
 *  its type is set to REPLY
 *
 * @param code the code
 * @param reply the reply
 *
 * @return the created packet
*/
packet_t *build_reply_packet(int code, reply_t *reply)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = REPLY;
    packet->is_global = false;
    memcpy(packet->packet_body, reply, REPLY_SIZE);
    return packet;
}

/**
 * @brief Build a packet with a code and a channel informations
 * @details Build a packet with the given code and channel, its type is set to
 *        CHANNEL
 *
 * @param code the code
 * @param channel the channel
 *
 * @return the created packet
*/
packet_t *build_channel_packet(int code, channel_t *channel)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = CHANNEL;
    packet->is_global = false;
    memcpy(packet->packet_body, channel, CHANNEL_SIZE);
    return packet;
}

/**
 * @brief Build a message packet
 * @details Build a packet with the given code and message, its type is set to
 *       MESSAGE
 *
 * @param code the code
 * @param body the body
 * @param sender_uuid the sender_uuid
 * @param receiver_uuid the receiver_uuid
 *
 * @return the created packet
*/
packet_t *build_message_packet(int code, message_t *message)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = MESSAGE;
    packet->is_global = false;
    memcpy(packet->packet_body, message, MESSAGE_SIZE);
    return packet;
}
