/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_client
*/

#include "clientllist.h"
#include "server_teams.h"
#include "reply_code.h"

/**
 * @brief Initialize the client buffers
 * @details Initialize the client buffers to NULL
 *
 * @param client the client
*/
static void initialize_client_buffers(client_t client)
{
    client->command = NULL;
    client->next_commands = NULL;
    client->args = NULL;
    client->buffer = NULL;
    client->team_uuid = NULL;
    client->channel_uuid = NULL;
    client->thread_uuid = NULL;
}

/**
 * @brief Create a client
 * @details Create a client with the given fd and ip
 *
 * @param fd the file descriptor
 * @param ip the ip
 *
 * @return the created client
*/
client_t create_client(int fd)
{
    client_t client = my_malloc(sizeof(struct client_s));

    if (!client)
        my_exit(84);
    initialize_client_buffers(client);
    client->fd = fd;
    client->next = NULL;
    client->data_status = READING;
    client->packet_queue = NULL;
    add_packet_to_queue(&client->packet_queue, build_packet(NEW_USER, ""));
    client->user = NULL;
    return client;
}
