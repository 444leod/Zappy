/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#pragma once

#include "client_types.h"
#include "server_info.h"
#include "macros.h"
#include <sys/select.h>
#include <stdbool.h>

typedef struct client_s *client_t;

typedef struct command_s {
    char *command;
    void (*func)(char **args, client_t clients,
        server_info_t server_info);
    uint32_t wait_units;
    enum CLIENT_TYPE client_type;
} command_t;

void msz(char **args, client_t client, server_info_t server_info);

void forward(char **args, client_t client,
    server_info_t server_info);

void unknown_command(char **args, client_t client,
    server_info_t server_info);

extern const command_t commands[];
