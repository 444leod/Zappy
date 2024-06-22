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
#include "debug.h"
#include <stdio.h>

/**
 * @brief Sends start information to graphical client
 */
static void start_graphical_client(client_t client, server_info_t server_info)
{
    char *msg = NULL;
    incantation_list_t rituals = server_info->rituals;
    egg_list_t eggs = get_team_eggs(NULL, server_info->map);
    egg_list_t next_egg = NULL;

    queue_buffer(client, "ok");
    for (; eggs; eggs = next_egg) {
        next_egg = eggs->next;
        msg = my_snprintf("enw %d -1 %d %d\n", eggs->egg->number,
            eggs->egg->pos.x, eggs->egg->pos.y);
        queue_buffer(client, msg);
        my_free(msg);
        my_free(eggs);
    }
    for (; rituals; rituals = rituals->next)
        send_pic(rituals->incantation);
}

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
 * @param team_name the team name
 * @param server_info the server informations
 * @param client the client that executed the command
 *
 * @return true if the team name is valid, false otherwise
 */
static bool is_team_name_valid(const char *team_name,
    const server_info_t server_info, const client_t client)
{
    team_list_t teams = server_info->teams;
    const team_t team = get_team_by_name(team_name, teams);
    char *escaped_string = get_escaped_string(team_name);

    if (team == NULL) {
        printf("Client %d: Invalid team name (%s)\n", client->fd,
            escaped_string);
        my_free(escaped_string);
        return false;
    }
    if (team->remaining_slots == 0) {
        printf("Client %d: Team %s is full\n", client->fd, escaped_string);
        my_free(escaped_string);
        return false;
    }
    my_free(escaped_string);
    return true;
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
        my_snprintf("%d", client->player->team->remaining_slots);

    queue_buffer(client, packet_string);
    my_free(packet_string);
    packet_string = my_snprintf("%d %d", width, height);
    queue_buffer(client, packet_string);
    my_free(packet_string);
}

/**
 * @brief Spawn the player in its given team
 * @details Spawn the player in its given team
 *
 * @param egg the egg to spawn the player
 * @param team the team of the player
 * @param client the client that executed the command
 * @param server_info the server informations
 */
static void spawn_player(const egg_t egg, const team_t team,
    const client_t client, const server_info_t server_info)
{
    player_t player = egg_to_player(egg, server_info->map);
    static uint32_t actual_number = 0;

    client->player = player;
    client->player->team = team;
    client->player->player_number = actual_number;
    client->player->rocks = (rocks_t){0, 0, 0, 0, 0, 0};
    client->team_client_number = team->actual_number;
    team->actual_number++;
    actual_number++;
    team->remaining_slots--;
    add_to_list((void *)client, (node_t *)&team->players);
    printf("Client %d: Connected as %s\n", client->fd,
        get_escaped_string(team->name));
    DEBUG_PRINT("[DEBUG] Player %d spawned as with egg %d at pos %d %d\n",
        client->player->player_number, egg->number, egg->pos.x,
        egg->pos.y);
}

/**
 * @brief Try to spawn a player
 * @details Try to spawn a player to the given team
 *       will print an error message if no egg is found
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server informations
 */
static void try_spawn_player(char **args, const client_t client,
    const server_info_t server_info)
{
    const team_t team = get_team_by_name(args[0], server_info->teams);
    egg_t egg = get_random_egg(team, server_info->map);

    if (egg == NULL) {
        printf("Client %d: No egg found for team %s\n", client->fd, args[0]);
        queue_buffer(client, "ko");
        return;
    }
    client->type = AI;
    spawn_player(egg, team, client, server_info);
    send_start_informations(client, server_info->width, server_info->height);
    queue_to_graphical(get_new_player_string(client->player));
}

/**
 * @brief Authenticate the client
 * @details Authenticate the client as a graphical or an AI client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server informations
 */
void auth(char **args, const client_t client,
    const server_info_t server_info)
{
    DEBUG_PRINT("[DEBUG] Authentificating %d\n", client->fd);
    if (tablen((const void **)args) != 1) {
        printf("Client %d: Bad team name\n", client->fd);
        queue_buffer(client, "ko");
        return;
    }
    if (strcmp(args[0], "GRAPHIC") == 0) {
        client->type = GRAPHICAL;
        printf("Client %d: Connected as GRAPHIC\n", client->fd);
        start_graphical_client(client, server_info);
        return;
    }
    if (!is_team_name_valid(args[0], server_info, client)) {
        queue_buffer(client, "ko");
        return;
    }
    try_spawn_player(args, client, server_info);
}
