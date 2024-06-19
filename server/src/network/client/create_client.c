/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** create_client
*/

#include "clients.h"
#include "garbage_collector.h"

/**
 * @brief Create a client
 * @details Create a client with the given fd
 *
 * @param fd the file descriptor
 *
 * @return the created client
*/
client_t create_client(const int fd)
{
    client_t client = my_malloc(sizeof(struct client_s));

    client->fd = fd;
    client->commands = NULL;
    client->buffer = NULL;
    client->type = NONE;
    client->player = NULL;
    client->team_client_number = 0;
    client->packet_queue = NULL;
    add_packet_to_queue(&client->packet_queue, build_packet("WELCOME"));
    return client;
}
