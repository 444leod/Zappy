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
    struct timespec handledTime;
    bool initialized;
    double waitDuration;
    command_t commandHandler;
} *client_command_t;

typedef struct client_command_list_s {
    struct client_command_list_s *next;
    struct client_command_list_s *prev;
    client_command_t command;
} *client_command_list_t;
