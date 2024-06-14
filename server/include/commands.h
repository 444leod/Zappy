/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#define ARGS char **args, const client_t client, const server_info_t serverInfo
#pragma once

#include "client_types.h"
#include "server_info.h"
#include "macros.h"
#include <sys/select.h>
#include <stdbool.h>

typedef struct client_s *client_t;

typedef struct command_s {
    char *command;
    void (*func)(ARGS);
    uint32_t waitUnits;
    enum CLIENT_TYPE ClientType;
} command_t;

extern const command_t COMMANDS[];
extern const command_t AUTHENTIFICATION_COMMAND;

///////////////////////////////////////////////////////////////////////////////
// GRAPHICAL COMMANDS

void msz(ARGS);

///////////////////////////////////////////////////////////////////////////////
// AI COMMANDS

void forward(ARGS);
void right(ARGS);
void left(ARGS);
void look(ARGS);
void inventory(ARGS);
void connect_nbr(ARGS);
void fork_player(ARGS);
void eject(ARGS);

///////////////////////////////////////////////////////////////////////////////
// OTHER COMMANDS

void unknown_command(ARGS);
void auth(ARGS);
