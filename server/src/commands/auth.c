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
#include <stdio.h>

/**
 * @brief Check if the team name is valid
 * @details Check if the team name is in the server team list
 *
 * @param name the team name
 * @param serverInfo the server informations
 * @return true if the team name is valid, false otherwise
 */
static bool is_team_name_valid(char *name, server_info_t serverInfo)
{
    team_list_t teams = serverInfo->teams;

    while (teams) {
        if (strcmp(teams->team->name, name) == 0) {
            return true;
        }
        teams = teams->next;
    }
    return false;
}

/**
 * @brief Send a "ko" message to the client
 *
 * @param client the client to send the message to
 */
static void send_ko(client_t client)
{
    const char *msg = "ko\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packetQueue, packet);
}

/**
 * @brief Send a "ok" message to the client
 *
 * @param client the client to send the message to
 */
static void send_ok(client_t client)
{
    const char *msg = "ok\n";
    packet_t *packet = build_packet(msg);

    add_packet_to_queue(&client->packetQueue, packet);
}

/**
 * @brief Update the client team
 * @details Update the client team and set the client number
 *
 * @param teamName the team name
 * @param client the client to update
 * @param teams the server teams list
 */
static void update_client_team(char *teamName, client_t client,
    team_list_t teams)
{
    team_t team;

    while (teams) {
        if (strcmp(teams->team->name, teamName) == 0) {
            team = teams->team;
            break;
        }
        teams = teams->next;
    }
    client->team = team;
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
static void send_start_informations(client_t client, uint32_t width,
    uint32_t height)
{
    packet_t *packet;

    packet = build_packet(my_snprintf("%d", client->team->remainingSlots));
    add_packet_to_queue(&client->packetQueue, packet);
    packet = build_packet(my_snprintf("%d %d", width, height));
    add_packet_to_queue(&client->packetQueue, packet);
}

/**
 * @brief Authenticate the client
 * @details Authenticate the client as a graphical or an AI client
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param serverInfo the server informations
 */
void auth(char **args, client_t client,
    server_info_t serverInfo)
{
    if (args[0] == NULL) {
        printf("Client %d: No team name\n", client->fd);
        send_ko(client);
        return;
    }
    if (strcmp(args[0], "GRAPHIC") == 0) {
        client->type = GRAPHICAL;
        printf("Client %d: Connected as GRAPHIC\n", client->fd);
        send_ok(client);
        return;
    }
    if (!is_team_name_valid(args[0], serverInfo)) {
        printf("Client %d: Invalid team name (%s)\n", client->fd,
            get_escaped_string(args[0]));
        send_ko(client);
        return;
    }
    client->type = AI;
    update_client_team(args[0], client, serverInfo->teams);
    send_start_informations(client, serverInfo->width, serverInfo->height);
}
