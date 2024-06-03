/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands_list
*/

#pragma once

#include <stdbool.h>
#include "commands.h"

typedef struct client_command_s {
    char *command;
    char **args;
    clock_t handled_at;
    bool initialized;
    double seconds_to_wait;
    command_t command_handler;
} *client_command_t;

typedef struct client_commands_s {
    struct client_commands_s *next;
    client_command_t command;
} *client_commands_t;
