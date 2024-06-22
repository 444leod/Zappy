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
#include "garbage_collector.h"
#include <sys/select.h>
#include <stdbool.h>

typedef struct client_s *client_t;

typedef struct command_s {
    char *command;
    void (*func)(char **args, const client_t clients,
        const server_info_t server_info);
    uint32_t execution_ticks;
    enum CLIENT_TYPE client_type;
} command_t;

void unknown_command(char **args, const client_t client,
    const server_info_t server_info);

void auth(char **args, const client_t client,
    const server_info_t server_info);

void forward(char **args, const client_t client,
    const server_info_t server_info);

void msz(char **args, const client_t client,
    const server_info_t server_info);

void bct(char **args, const client_t client,
    const server_info_t server_info);

void mct(char **args, const client_t client,
    const server_info_t server_info);

void tna(char **args, const client_t client,
    const server_info_t server_info);

void ppo(char **args, const client_t client,
    const server_info_t server_info);

void plv(char **args, const client_t client,
    const server_info_t server_info);

void pin(char **args, const client_t client,
    const server_info_t server_info);

void sgt(char **args, const client_t client,
    const server_info_t server_info);

void sst(char **args, const client_t client,
    const server_info_t server_info);

extern const command_t COMMANDS[];
extern const command_t AUTHENTIFICATION_COMMAND;

player_t get_player_by_player_number(const uint32_t player_number);
char get_char_by_orientation(int orientation);
