/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ebo
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the egg player connexion string
 *
 * @param egg the egg
 * @return char* the string
 */
char *get_egg_player_connexion_string(const egg_t egg)
{
    return my_snprintf("ebo %d", egg->number);
}

/**
 * @brief Send the egg player connexion to the client
 *
 * @param client the client
 * @param egg the egg
 */
void send_egg_player_connexion_to_client(const client_t client,
    const egg_t egg)
{
    char *egg_player_connexion_string = get_egg_player_connexion_string(egg);

    queue_buffer(client, egg_player_connexion_string);
    my_free(egg_player_connexion_string);
}

/**
 * @brief Send the egg player connexion to all the clients in the list
 *
 * @param clients the list of clients
 * @param egg the egg
 */
void send_egg_player_connexion_to_client_list(const client_list_t clients,
    const egg_t egg)
{
    client_list_t tmp = clients;
    char *egg_player_connexion_string = get_egg_player_connexion_string(egg);

    while (tmp) {
        queue_buffer(tmp->client, egg_player_connexion_string);
        tmp = tmp->next;
    }
    my_free(egg_player_connexion_string);
}

/**
 * @brief Send the egg player connexion to the graphical clients
 *
 * @param egg the egg
 */
void send_egg_player_connexion_to_graphical(const egg_t egg)
{
    client_list_t graphical_clients = get_clients_by_type(GRAPHICAL);
    client_list_t tmp = graphical_clients;

    send_egg_player_connexion_to_client_list(graphical_clients, egg);
    while (graphical_clients) {
        tmp = graphical_clients->next;
        my_free(graphical_clients);
        graphical_clients = tmp;
    }
}
