/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** build_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include <unistd.h>
#include <string.h>

/**
 * @brief Build a packet with a string
 * @details Build a packet with the given code and buffer, its type is set to
 *        NONE
 *
 * @param code the code
 * @param buffer the buffer
 *
 * @return the created packet
*/
packet_t *build_packet(int code, char *buffer)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = NONE;
    packet->is_global = false;
    memset(packet->packet_body, 0, sizeof(packet->packet_body));
    memcpy(packet->packet_body, buffer, strlen(buffer));
    return packet;
}

/**
 * @brief Build a packet with a code, buffer and packet type
 * @details Build a packet with the given code, buffer and packet type
 *
 * @param code the code
 * @param buffer the buffer
 * @param packet_type the packet type
 *
 * @return the created packet
*/
packet_t *build_custom_packet(int code, char *buffer, int packet_type)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = packet_type;
    packet->is_global = false;
    memset(packet->packet_body, 0, sizeof(packet->packet_body));
    memcpy(packet->packet_body, buffer, strlen(buffer));
    return packet;
}

/**
 * @brief Build a packet with a code and a user information
 * @details Build a packet with the given code and user information, its type
 *       is set to USER_INFORMATION
 *
 * @param code the code
 * @param username the username
 * @param uuid the uuid
 * @param is_logged the is_logged
 *
 * @return the created packet
*/
packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid,
    bool is_logged)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    user_information_t *user = my_malloc(USER_INFORMATION_SIZE);

    packet->code = code;
    packet->packet_type = USER_INFORMATION;
    packet->is_global = false;
    memcpy(user->username, username, sizeof(username_t));
    memcpy(user->user_uuid, uuid, sizeof(uuid_t));
    user->is_logged = is_logged;
    memcpy(packet->packet_body, user, USER_INFORMATION_SIZE);
    return packet;
}

/**
 * @brief Build a error packet with a code and a buffer
 * @details Build a packet with the given code and buffer, its type is set to
 *       ERROR
 *
 * @param code the code
 * @param buffer the buffer
 *
 * @return the created packet
*/
packet_t *build_error_packet(int code, char *buffer)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = ERROR;
    packet->is_global = false;
    memset(packet->packet_body, 0, sizeof(packet->packet_body));
    memcpy(packet->packet_body, buffer, strlen(buffer));
    return packet;
}
