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
        const server_info_t serverInfo);
    uint32_t waitUnits;
    enum CLIENT_TYPE ClientType;
} command_t;

void unknown_command(char **args, const client_t client,
    const server_info_t serverInfo);

void auth(char **args, const client_t client,
    const server_info_t serverInfo);

void forward(char **args, const client_t client,
    const server_info_t serverInfo);

void msz(char **args, const client_t client,
    const server_info_t serverInfo);

void bct(char **args, const client_t client,
    const server_info_t serverInfo);

void mct(char **args, const client_t client,
    const server_info_t serverInfo);

void tna(char **args, const client_t client,
    const server_info_t serverInfo);

void ppo(char **args, const client_t client,
    const server_info_t serverInfo);

void plv(char **args, const client_t client,
    const server_info_t serverInfo);

extern const command_t COMMANDS[];
extern const command_t AUTHENTIFICATION_COMMAND;

void send_tile_content(const client_t client, const server_info_t serverInfo,
    const position_t pos);
player_t get_player_by_player_number(const uint32_t playerNumber);
char get_char_by_orientation(int orientation);
