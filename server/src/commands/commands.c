/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#include "commands.h"
#include <stddef.h>

/**
 * @brief The commands
 * @details The string command and its function
*/
const command_t COMMANDS[] = {
    {"msz", &msz, 0, GRAPHICAL},
    {"Forward", &forward, 7, AI},
    {NULL, &unknown_command, 0, NONE}
};
