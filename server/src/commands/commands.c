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
    {"bct", &bct, 0, GRAPHICAL},
    {"mct", &mct, 0, GRAPHICAL},
    {"tna", &tna, 0, GRAPHICAL},
    {"ppo", &ppo, 0, GRAPHICAL},
    {"plv", &plv, 0, GRAPHICAL},
    {"pin", &pin, 0, GRAPHICAL},
    {"Forward", &forward, 7, AI},
    {NULL, &unknown_command, 0, NONE}
};
