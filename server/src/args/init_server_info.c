/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_server_info
*/

#include "zappy.h"
#include "garbage_collector.h"
#include "params.h"
#include "teams.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief Initialize the port
 * @details correctly initialize the port in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_port(param_t params, server_info_t serverInfo)
{
    param_t port = get_param("-p", params);

    serverInfo->port = atoi(port->informations->content);
    port->informations->handled = true;
}

/**
 * @brief Initialize the clients number
 * @details correctly initialize the clients number in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_clients_number(param_t params, server_info_t serverInfo)
{
    param_t clientsNb = get_param("-c", params);

    serverInfo->clientsNb = atoi(clientsNb->informations->content);
    clientsNb->informations->handled = true;
}

/**
 * @brief Initialize the width
 * @details correctly initialize the width in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_width(param_t params, server_info_t serverInfo)
{
    param_t width = get_param("-x", params);

    serverInfo->width = atoi(width->informations->content);
    width->informations->handled = true;
}

/**
 * @brief Initialize the height
 * @details correctly initialize the height in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_height(param_t params, server_info_t serverInfo)
{
    param_t height = get_param("-y", params);

    serverInfo->height = atoi(height->informations->content);
    height->informations->handled = true;
}

/**
 * @brief Initialize the frequency
 * @details correctly initialize the frequency in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_freq(param_t params, server_info_t serverInfo)
{
    param_t freq = get_param("-f", params);

    serverInfo->freq = atoi(freq->informations->content);
    freq->informations->handled = true;
}

/**
 * @brief Get the list of arguments until the next flag or the end of the list
 * @details get the list of arguments until the next flag or the end of the
 *   arguments list
 *
 * @param params the arguments
 *
 * @return the arguments list until the next flag or the end of the list
*/
static param_t get_until_flag(param_t params)
{
    param_t new = NULL;
    param_t tmp = params;

    while (tmp && tmp->informations->content[0] != '-') {
        add_to_list((void *)tmp->informations, (node_t *)&new);
        tmp->informations->handled = true;
        tmp = tmp->next;
    }
    return new;
}

/**
 * @brief Initialize the teams
 * @details correctly initialize the teams in the serverInfo struct
 *
 * @param params the arguments
 * @param serverInfo the serverInfo struct
*/
static void init_teams(param_t params, server_info_t serverInfo)
{
    param_t teamValue = get_param("-n", params);
    param_t teamNames = get_until_flag(teamValue);
    team_t team;

    while (teamNames) {
        team = my_malloc(sizeof(struct team_s));
        team->name = teamNames->informations->content;
        team->actualNumber = 0;
        team->remainingSlots = 0;
        add_to_list((void *)team, (node_t *)&serverInfo->teams);
        teamNames = teamNames->next;
    }
}

/**
 * @brief Update the max clients of each teams.
 * @details Update the max clients of each teams.
 *
 * @param teamsList the list of teams (linked list)
 * @param clientsNb the maximum number of clients
*/
static void update_teams_max_clients(team_list_t teamsList, uint32_t clientsNb)
{
    team_list_t tmp = teamsList;

    while (tmp) {
        tmp->team->remainingSlots = clientsNb;
        tmp = tmp->next;
    }
}

/**
 * @brief Initialize the serverInfo struct
 * @details correctly initialize the serverInfo struct with the port and the
 *    path of the server
 *
 * @param argv the arguments of the program
 *
 * @return the serverInfo struct
*/
server_info_t init_server_info(const char *argv[])
{
    server_info_t serverInfo = my_malloc(sizeof(struct server_info_s));
    param_t params = NULL;
    param_informations_t param = NULL;

    for (uint16_t i = 1; argv[i]; i++) {
        param = my_malloc(sizeof(struct param_informations_s));
        param->content = my_strdup(argv[i]);
        param->handled = false;
        add_to_list((void *)param, (node_t *)&params);
    }
    init_teams(params, serverInfo);
    init_port(params, serverInfo);
    init_width(params, serverInfo);
    init_height(params, serverInfo);
    init_clients_number(params, serverInfo);
    init_freq(params, serverInfo);
    update_teams_max_clients(serverInfo->teams, serverInfo->clientsNb);
    serverInfo->map = create_map(serverInfo->width, serverInfo->height);
    init_map(serverInfo->map);
    return serverInfo;
}
