/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** auth
*/

#include "commands.h"
#include "packet.h"
#include "clients.h"
#include "lib.h"
#include "zappy.h"
#include "game.h"
#include <stdio.h>

/**
 * @brief Get a team by its name
 * @details Get a team by its name in the server team list
 *
 * @param name the team name
 * @param teams the server teams list
 *
 * @return the team if found, NULL otherwise
 */
static team_t get_team_by_name(const char *name, team_list_t teams)
{
    team_t team = NULL;

    while (teams) {
        if (strcmp(teams->team->name, name) == 0) {
            team = teams->team;
            break;
        }
        teams = teams->next;
    }
    return team;
}

/**
 * @brief Check if the team name is valid
 * @details Check if the team name is in the server team list
 *        and if the team is not full
 *        will print an error message if the team is invalid
 *
 * @param teamName the team name
 * @param serverInfo the server informations
 * @param client the client that executed the command
 *
 * @return true if the team name is valid, false otherwise
 */
static bool is_team_name_valid(const char *teamName,
    const server_info_t serverInfo, const client_t client)
{
    team_list_t teams = serverInfo->teams;
    const team_t team = get_team_by_name(teamName, teams);

    if (team == NULL) {
        printf("Client %d: Invalid team name (%s)\n", client->fd,
            get_escaped_string(teamName));
        return false;
    }
    if (team->remainingSlots == 0) {
        printf("Client %d: Team %s is full\n", client->fd,
            get_escaped_string(teamName));
        return false;
    }
    return true;
}

/**
 * @brief Update the client team
 * @details Update the client team and set the client number
 *
 * @param teamName the team name
 * @param client the client to update
 * @param teams the server teams list
 */
static void update_client_team(const char *teamName, const client_t client,
    server_info_t server)
{
    const team_t team = get_team_by_name(teamName, server->teams);
    egg_t egg = get_random_egg(team, server->map);
    player_t player = egg_to_player(egg, server->map);

    client->player = player;
    team->remainingSlots--;
    client->clientNumber = team->actualNumber;
    team->actualNumber++;
    printf("Client %d: Connected as %s\n", client->fd,
        get_escaped_string(teamName));
}

/**
 * @brief Send the start informations to the client
 * @details Send the remaining slots of the team and the map size
 *
 * @param client the client to send the informations to
 * @param width the width of the map
 * @param height the height of the map
 */
static void send_start_informations(const client_t client,
    const uint32_t width, const uint32_t height)
{
    queue_buffer(client,
        my_snprintf("%d", client->player->team->remainingSlots));
    queue_buffer(client,
        my_snprintf("%d %d", width, height));
}

/**
 * @brief Authenticate the client
 * @details Authenticate the client as a graphical or an AI client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server informations
 */
void auth(char **args, const client_t client,
    const server_info_t serverInfo)
{
    if (tablen((const void **)args) != 1) {
        printf("Client %d: Bad team name\n", client->fd);
        queue_buffer(client, "ko");
        return;
    }
    if (strcmp(args[0], "GRAPHIC") == 0) {
        client->type = GRAPHICAL;
        printf("Client %d: Connected as GRAPHIC\n", client->fd);
        queue_buffer(client, "ok");
        return;
    }
    if (!is_team_name_valid(args[0], serverInfo, client)) {
        queue_buffer(client, "ko");
        return;
    }
    client->type = AI;
    update_client_team(args[0], client, serverInfo);
    send_start_informations(client, serverInfo->width, serverInfo->height);
}
