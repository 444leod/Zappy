/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tna
*/

#include "commands.h"
#include "packet.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the team name string
 *
 * @param team the team
 * @return char* the team name string
 */
char *get_team_name_string(const team_t team)
{
    return my_snprintf("tna %s", team->name);
}

/**
 * @brief Get the team name string list
 *
 * @param teams the team list
 * @return char* the team name string list
 */
char *get_team_name_string_list(const team_list_t teams)
{
    char *team_name_list_string = "";
    char *tmp = "";
    team_list_t tmp_teams = teams;

    while (tmp_teams) {
        tmp = get_team_name_string(tmp_teams->team);
        team_name_list_string = supercat(3, team_name_list_string, "\n", tmp);
        my_free(tmp);
        tmp_teams = tmp_teams->next;
    }
    return team_name_list_string;
}

/**
 * @brief Send the team name to a client
 *
 * @param client the client that executed the command
 * @param team_name the team name
 */
void send_team_name_list_to_client(const client_t client,
    const team_list_t teams)
{
    char *team_name_string;
    team_list_t tmp = teams;

    while (tmp) {
        team_name_string = get_team_name_string(tmp->team);
        queue_buffer(client, team_name_string);
        my_free(team_name_string);
        tmp = tmp->next;
    }
}

/**
 * @brief Send the team name to all the clients in the list
 *
 * @param clients the list of clients
 * @param team_name the team name
 */
void send_team_name_list_to_client_list(const client_list_t clients,
    const team_list_t teams)
{
    char *team_name_string;
    team_list_t tmp_teams = teams;
    client_list_t tmp_clients = clients;

    while (tmp_teams) {
        team_name_string = get_team_name_string(tmp_teams->team);
        while (tmp_clients) {
            queue_buffer(tmp_clients->client, team_name_string);
            tmp_clients = tmp_clients->next;
        }
        my_free(team_name_string);
    }
}

/**
 * @brief Tna command
 * @details Send the team names to a client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void tna(char **args, const client_t client,
    const server_info_t server_info)
{
    if (tablen((const void **)args) > 1) {
        printf("Client %d: tna: bad argument number\n", client->fd);
        queue_buffer(client, "sbp");
        return;
    }
    send_team_name_list_to_client(client, server_info->teams);
}
