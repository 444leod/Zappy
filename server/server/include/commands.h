/*
** EPITECH PROJECT, 2024
** myTeams
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

void create(client_t client, char **command);
void info(client_t client, char **command);
void list(client_t client, char **command);
void login(client_t client, char **command);
void logout(client_t client, char **command);
void messages(client_t client, char **command);
void my_send(client_t client, char **command);
void subscribe(client_t client, char **command);
void subscribed(client_t client, char **command);
void unsubscribe(client_t client, char **command);
void use(client_t client, char **command);
void user(client_t client, char **command);
void users(client_t client, char **command);
void unknown_command(client_t client, char **command);

extern const command_t commands[];
