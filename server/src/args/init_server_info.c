/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_server_info
*/

#include "zappy.h"
#include "garbage_collector.h"
#include "params.h"
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
    param_t clientsNb = get_param("-c", params);

    server_info->clientsNb = atoi(clientsNb->informations->content);
    clientsNb->informations->handled = true;
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
    param_t team = get_param("-n", params);
    param_t team_names = get_until_flag(team);

    while (team_names) {
        add_to_list((void *)team_names->informations->content,
            (node_t *)&server_info->team_names);
        team_names = team_names->next;
    }
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
server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = my_malloc(sizeof(struct server_info_s));
    param_t params = NULL;
    param_informations_t param = NULL;

    for (uint16_t i = 1; argv[i]; i++) {
        param = my_malloc(sizeof(struct param_informations_s));
        param->content = argv[i];
        param->handled = false;
        add_to_list((void *)param, (node_t *)&params);
    }
    init_teams(params, server_info);
    init_port(params, server_info);
    init_width(params, server_info);
    init_height(params, server_info);
    init_clients_number(params, server_info);
    init_freq(params, server_info);
    return server_info;
}
