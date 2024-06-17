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
#include "garbage_collector.h"
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
void bct(ARGS);
void mct(ARGS);
void tna(ARGS);
void ppo(ARGS);
void plv(ARGS);
void pin(ARGS);
void sgt(ARGS);
void sst(ARGS);

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
void take(ARGS);
void set(ARGS);

///////////////////////////////////////////////////////////////////////////////
// OTHER COMMANDS

void unknown_command(ARGS);
void auth(ARGS);

extern const command_t COMMANDS[];
extern const command_t AUTHENTIFICATION_COMMAND;

///////////////////////////////////////////////////////////////////////////////
// UTILS

bool assert_argv_count(char **args, uint32_t expected);
void throw_ko(client_t client);
player_t get_player_by_player_number(const uint32_t playerNumber);
char get_char_by_orientation(int orientation);
