/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#include "commands.h"
#include <stddef.h>

const command_t UNKNOWN_COMMAND = {NULL, &unknown_command, 0, NONE};
const command_t AUTHENTIFICATION_COMMAND = {NULL, &auth, 0, NONE};

/**
 * @brief The commands
 * @details The string command and its function
*/
const command_t COMMANDS[] = {
    {"msz", &msz, 0, GRAPHICAL},

    {"Forward", &forward, 7, AI},
    {"Right", &right, 7, AI},
    {"Left", &left, 7, AI},
    {"Look", &look, 7, AI},
    {"Inventory", &inventory, 1, AI},
    {"Connect_nbr", &connect_nbr, 7, AI},
    {"Fork", &fork_player, 42, AI},

    {NULL, &unknown_command, 0, NONE}
};
