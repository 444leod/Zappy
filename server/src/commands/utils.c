/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#include "commands.h"
#include "zappy.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Get a player by its player number
 *
 * @param player_number The player number
 * @return player_t The player
 */
player_t get_player_by_player_number(const uint32_t player_number)
{
    client_list_t *clients = get_clients();
    client_list_t client_node;

    if (!clients)
        return (NULL);
    client_node = *clients;
    while (client_node) {
        if (client_node->client->player &&
            client_node->client->player->player_number == player_number)
            return (client_node->client->player);
        client_node = client_node->next;
    }
    return (NULL);
}

/**
 * @brief Get the orientation char by the orientation enum
 *
 * @param orientation The orientation enum
 *
 * @return char The orientation char
 * @return -1 If the orientation is invalid
 */
char get_char_by_orientation(int orientation)
{
    switch (orientation) {
        case 1:
            return ('N');
        case 2:
            return ('E');
        case 3:
            return ('S');
        case 4:
            return ('W');
    }
    return -1;
}

/**
 * @brief Adds a KO packet to queue
 * @param client the client
 */
void throw_ko(client_t client)
{
    add_packet_to_queue(&client->packet_queue, build_packet("ko"));
}

/**
 * @brief Prepends a command to a player
 * @param client The client
 * @param command The command
 */
void prepend_client_command(client_t client, client_command_t command)
{
    client_command_list_t new_cmd = NULL;

    new_cmd = my_malloc(sizeof(struct client_command_list_s));
    new_cmd->command = command;
    if (client->commands != NULL) {
        new_cmd->prev = client->commands;
        new_cmd->next = client->commands->next;
        client->commands->next = new_cmd;
    } else {
        new_cmd->next = NULL;
        new_cmd->prev = NULL;
        client->commands = new_cmd;
    }
}

/**
 * @brief Queue the given buffer to all the graphical clients
 * @details Queue the given buffer to all the graphical clients
 *
 * @param buffer the buffer to queue
 */
void queue_to_graphical(char *buffer)
{
    client_list_t graphical_clients = get_clients_by_type(GRAPHICAL);

    while (graphical_clients) {
        queue_buffer(graphical_clients->client, buffer);
        graphical_clients = graphical_clients->next;
    }
    my_free(buffer);
}
