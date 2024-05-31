/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#pragma once

#include "server_teams.h"
#include <sys/select.h>
#include <stdbool.h>

typedef struct command_s {
    char *command;
    void (*func)(client_t, char **);
} command_t;

void msz(client_t client, char **command);
void unknown_command(client_t client, char **command);

extern const command_t commands[];
