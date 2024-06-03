/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#include "commands.h"

/**
 * @brief The commands
 * @details The string command and its function
*/
const command_t commands[] = {
    {"msz", &msz},
    {NULL, &unknown_command}
};
