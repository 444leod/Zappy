/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** check_args
*/

#include "zappy.h"

/**
 * @brief Check the number of arguments
 * @details Check if the number of arguments is valid (2)
 *
 * @param argc the number of arguments
*/
static void check_args_number(int argc)
{
    if (argc != 2) {
        printf("Usage: ./myteams_server port\n");
        my_exit(84);
    }
}

/**
 * @brief Check the port
 * @details Check if the port is valid (only numbers)
 *
 * @param port the port to check
*/
static void check_port(char *port)
{
    for (int i = 0; port[i]; i++)
        if (port[i] < '0' || port[i] > '9')
            my_error("Invalid port");
}

/**
 * @brief Check the arguments
 * @details Check the number of arguments, the port and the path
 *    and exit if one of them is invalid
 *
 * @param argc the number of arguments
 * @param argv the arguments
*/
void check_args(int argc, char *argv[])
{
    check_args_number(argc);
    check_port(argv[1]);
}
