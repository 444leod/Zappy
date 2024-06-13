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
    client->next = NULL;
    client->commands = NULL;
    client->buffer = NULL;
    client->type = NONE;
    client->player = NULL;
    client->clientNumber = 0;
    client->packetQueue = NULL;
    add_packet_to_queue(&client->packetQueue, build_packet("WELCOME"));
    return client;
}
