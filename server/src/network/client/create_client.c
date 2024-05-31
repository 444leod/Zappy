/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** create_client
*/

#include "clients.h"
#include "zappy.h"

/**
 * @brief Create a client
 * @details Create a client with the given fd
 *
 * @param fd the file descriptor
 *
 * @return the created client
*/
client_t create_client(int fd)
{
    client_t client = my_malloc(sizeof(struct client_s));

    client->fd = fd;
    client->next = NULL;
    client->data_status = READING;
    client->command = NULL;
    client->type = NONE;
    client->next_commands = NULL;
    client->team = NULL;
    client->client_num = 0;
    client->packet_queue = NULL;
    add_packet_to_queue(&client->packet_queue, build_packet("WELCOME"));
    return client;
}
