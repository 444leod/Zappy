/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** check_args
*/

#include "zappy.h"
#include "params.h"
#include "lib.h"

/**
 * @brief Check the port
 * @details Check if the port is valid
 *
 * @param params the arguments
*/
static void check_port(param_t params)
{
    param_t port = get_param("-p", params);
    int port_number;

    if (port == NULL || !is_number(port->informations->content))
        display_help("Invalid port.\n");
    port_number = atoi(port->informations->content);
    if (port_number < 0 || port_number > 65535)
        display_help("Invalid port.\n");
    port->informations->handled = true;
}

/**
 * @brief Check the width
 * @details Check if the width is valid
 *
 * @param params the arguments
*/
static void check_width(param_t params)
{
    param_t width = get_param("-x", params);

    if (width == NULL || !is_number(width->informations->content))
        display_help("Invalid width.\n");
    if (atoi(width->informations->content) < 2)
        display_help("Invalid width (min 2).\n");
    width->informations->handled = true;
}

/**
 * @brief Check the height
 * @details Check if the height is valid
 *
 * @param params the arguments
*/
static void check_height(param_t params)
{
    param_t height = get_param("-y", params);

    if (height == NULL || !is_number(height->informations->content))
        display_help("Invalid height.\n");
    if (atoi(height->informations->content) < 2)
        display_help("Invalid height (min 2).\n");
    height->informations->handled = true;
}

/**
 * @brief Check the number of clients
 * @details Check if the number of clients is valid
 *
 * @param params the arguments
*/
static void check_clients_nb(param_t params)
{
    param_t clientsNb = get_param("-c", params);

    if (clientsNb == NULL || !is_number(clientsNb->informations->content))
        display_help("Invalid clientsNb.\n");
    if (atoi(clientsNb->informations->content) < 1)
        display_help("Invalid clientsNb (min 1).\n");
    clientsNb->informations->handled = true;
}

/**
 * @brief Check the frequency
 * @details Check if the frequency is valid
 *
 * @param params the arguments
*/
static void check_freq(param_t params)
{
    param_t freq = get_param("-f", params);

    if (freq == NULL || !is_number(freq->informations->content))
        display_help("Invalid freq.\n");
    if (atoi(freq->informations->content) < 1)
        display_help("Invalid freq (min 1).\n");
    freq->informations->handled = true;
}

/**
 * @brief Check the team names
 * @details Check if the team names are valid (not duplicate)
 *
 * @param actual_name the name to check
 * @param other_params the other team names
*/
static void check_name(char *actual_name, param_t other_params)
{
    while (other_params) {
        if (strcmp(actual_name, other_params->informations->content) == 0)
            display_help("Duplicate team names.\n");
        other_params = other_params->next;
    }
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
 * @brief Check the team names
 * @details Check if the team names are valid
 *
 * @param params the arguments
*/
static void check_team_names(param_t params)
{
    param_t team_names = get_param("-n", params);
    param_t tmp = NULL;

    if (team_names == NULL)
        display_help("-n is missing.\n");
    team_names = get_until_flag(team_names);
    if (get_list_size((node_t)team_names) < 2)
        display_help("Invalid team names (min 2).\n");
    tmp = team_names;
    while (team_names) {
        tmp = tmp->next;
        if (!is_alphanum(team_names->informations->content))
            display_help("Invalid team name.\n");
        check_name(team_names->informations->content, tmp);
        team_names = team_names->next;
    }
}

/**
 * @brief Check the handled parameters
 * @details Check if all the parameters have been handled
 *
 * @param params the arguments
*/
static void check_handled_parameters(param_t params)
{
    param_t tmp = params;

    while (tmp) {
        if (tmp->informations->handled == false)
            display_help("Wondering arguments.\n");
        tmp = tmp->next;
    }
}

/**
 * @brief Check the arguments
 * @details Check the number of arguments, the port, the width, the height,
 *   the number of clients, the frequency and the team names
 *
 * @param argc the number of arguments
 * @param argv the arguments
*/
void check_args(int argc, char *argv[])
{
    param_t params = NULL;
    param_informations_t param = NULL;

    if (argc < 14)
        display_help("Not enough parameters.\n");
    for (int i = 1; i < argc; i++) {
        param = malloc(sizeof(struct param_informations_s));
        param->content = argv[i];
        param->handled = false;
        add_to_list((void *)param, (node_t *)&params);
    }
    check_team_names(params);
    check_port(params);
    check_width(params);
    check_height(params);
    check_clients_nb(params);
    check_freq(params);
    check_handled_parameters(params);
}
