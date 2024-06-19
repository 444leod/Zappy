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
#include "time_utils.h"
#include "game.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief Initialize the port
 * @details correctly initialize the port in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_port(param_t params, server_info_t server_info)
{
    param_t port = get_param("-p", params);

    server_info->port = atoi(port->informations->content);
    port->informations->handled = true;
}

/**
 * @brief Initialize the clients number
 * @details correctly initialize the clients number in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_clients_number(param_t params, server_info_t server_info)
{
    param_t clients_nb = get_param("-c", params);

    server_info->clients_nb = atoi(clients_nb->informations->content);
    clients_nb->informations->handled = true;
}

/**
 * @brief Initialize the width
 * @details correctly initialize the width in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_width(param_t params, server_info_t server_info)
{
    param_t width = get_param("-x", params);

    server_info->width = atoi(width->informations->content);
    width->informations->handled = true;
}

/**
 * @brief Initialize the height
 * @details correctly initialize the height in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_height(param_t params, server_info_t server_info)
{
    param_t height = get_param("-y", params);

    server_info->height = atoi(height->informations->content);
    height->informations->handled = true;
}

/**
 * @brief Initialize the frequency
 * @details correctly initialize the frequency in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_freq(param_t params, server_info_t server_info)
{
    param_t freq = get_param("-f", params);

    server_info->freq = atoi(freq->informations->content);
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
 * @details correctly initialize the teams in the server_info struct
 *
 * @param params the arguments
 * @param server_info the server_info struct
*/
static void init_teams(param_t params, server_info_t server_info)
{
    param_t teamValue = get_param("-n", params);
    param_t teamNames = get_until_flag(teamValue);
    team_t team;

    while (teamNames) {
        team = my_malloc(sizeof(struct team_s));
        team->name = teamNames->informations->content;
        team->actual_number = 0;
        team->remaining_slots = 0;
        add_to_list((void *)team, (node_t *)&server_info->teams);
        teamNames = teamNames->next;
    }
}

/**
 * @brief Update the max clients of each teams.
 * @details Update the max clients of each teams.
 *
 * @param teamsList the list of teams (linked list)
 * @param clients_nb the maximum number of clients
*/
static void update_teams_max_clients(const team_list_t teamsList,
    const uint32_t clients_nb)
{
    team_list_t tmp = teamsList;

    while (tmp) {
        tmp->team->remaining_slots = clients_nb;
        tmp = tmp->next;
    }
}

/**
 * @brief Initialize the map
 * @details correctly initialize the map in the serverInfo struct
 *
 * @param server_info the serverInfo struct
*/
static void init_map(const server_info_t server_info)
{
    server_info->actual_rocks = (rocks_t){0, 0, 0, 0, 0, 0};
    server_info->actual_foods = 0;
    server_info->refill_wait = REFILL_TICKS / server_info->freq;
    server_info->last_refill_check = get_actual_time();
    server_info->map = create_map(server_info->width, server_info->height);
    fill_map(server_info->map, &server_info->actual_rocks,
        &server_info->actual_foods, server_info->teams);
}

/**
 * @brief Initialize the server_info struct
 * @details correctly initialize the server_info struct with the port and the
 *    path of the server
 *
 * @param argv the arguments of the program
 *
 * @return the server_info struct
*/
server_info_t init_server_info(const char *argv[])
{
    server_info_t server_info = my_malloc(sizeof(struct server_info_s));
    param_t params = NULL;
    param_informations_t param = NULL;

    for (uint16_t i = 1; argv[i]; i++) {
        param = my_malloc(sizeof(struct param_informations_s));
        param->content = my_strdup(argv[i]);
        param->handled = false;
        add_to_list((void *)param, (node_t *)&params);
    }
    init_teams(params, server_info);
    init_port(params, server_info);
    init_width(params, server_info);
    init_height(params, server_info);
    init_clients_number(params, server_info);
    init_freq(params, server_info);
    update_teams_max_clients(server_info->teams, server_info->clients_nb);
    server_info->map = create_map(server_info->width, server_info->height);
    init_map(server_info);
    return server_info;
}
