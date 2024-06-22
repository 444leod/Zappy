/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tna
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"
#include "commands_utils.h"

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
    char *team_name_list_string = NULL;
    char *tmp = "";
    team_list_t tmp_teams = teams;

    while (tmp_teams) {
        tmp = get_team_name_string(tmp_teams->team);
        if (team_name_list_string == NULL)
            team_name_list_string = my_strdup(tmp);
        else
            team_name_list_string =
                supercat(3, team_name_list_string, "\n", tmp);
        my_free(tmp);
        tmp_teams = tmp_teams->next;
    }
    return team_name_list_string;
}

/**
 * @brief Send the team names to a client
 *
 * @param client the client
 * @param server_info the server infos
 */
static void send_team_names_to_client(const client_t client,
    const server_info_t server_info)
{
    char *team_name_list_string =
        get_team_name_string_list(server_info->teams);

    queue_buffer(client, team_name_list_string);
    my_free(team_name_list_string);
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
    send_team_names_to_client(client, server_info);
}
