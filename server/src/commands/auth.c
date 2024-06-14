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
#include "commands_utils.h"
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
    char *escaped_string = get_escaped_string(teamName);

    if (team == NULL) {
        printf("Client %d: Invalid team name (%s)\n", client->fd,
            escaped_string);
        my_free(escaped_string);
        return false;
    }
    if (team->remainingSlots == 0) {
        printf("Client %d: Team %s is full\n", client->fd, escaped_string);
        my_free(escaped_string);
        return false;
    }
    my_free(escaped_string);
    return true;
}

/**
 * @brief Spawn the player in its given team
 *
 * @param teamName the team name
 * @param client the client that will spawn a player
 * @param server the serverInfo
 */
static void spawn_player(const char *teamName, const client_t client,
    server_info_t server)
{
    const team_t team = get_team_by_name(teamName, server->teams);
    egg_t egg = get_random_egg(team, server->map);
    player_t player = egg_to_player(egg, server->map);
    static uint32_t actualNumber = 0;

    client->player = player;
    client->player->rocks = (rocks_t){0, 0, 0, 0, 0, 0};
    team->remainingSlots--;
    client->teamClientNumber = team->actualNumber;
    client->player->playerNumber = actualNumber;
    team->actualNumber++;
    actualNumber++;
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
    char *packet_string =
        my_snprintf("%d", client->player->team->remainingSlots);

    queue_buffer(client, packet_string);
    my_free(packet_string);
    packet_string = my_snprintf("%d %d", width, height);
    queue_buffer(client, packet_string);
    my_free(packet_string);
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
    spawn_player(args[0], client, serverInfo);
    send_start_informations(client, serverInfo->width, serverInfo->height);
    send_new_player_to_graphical(client->player);
}
