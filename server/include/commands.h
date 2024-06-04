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
    void (*func)(char **args, const client_t clients,
        const server_info_t server_info);
    uint32_t wait_units;
    enum CLIENT_TYPE client_type;
} command_t;

void msz(char **args, const client_t client,
    const server_info_t server_info);

void forward(char **args, const client_t client,
    const server_info_t server_info);

void unknown_command(char **args, const client_t client,
    const server_info_t server_info);

extern const command_t COMMANDS[];
