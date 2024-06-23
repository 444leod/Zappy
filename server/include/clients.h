/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clients
*/

#pragma once

#include <stdlib.h>
#include <uuid/uuid.h>
#include "packet.h"
#include "linked_lists.h"
#include "commands.h"
#include "commands_list.h"
#include "client_types.h"
#include "teams.h"

typedef struct client_s {
    int fd;
    player_t player;
    uint16_t team_client_number;
    packet_queue_t packet_queue;
    enum CLIENT_TYPE type;
    client_command_list_t commands;
    char *buffer;
    bool end;
} *client_t;

typedef struct client_list_s {
    struct client_list_s *next;
    struct client_list_s *prev;
    client_t client;
} *client_list_t;

void add_client(const client_t client);
void remove_client(int fd);
client_t create_client(int fd);
client_list_t *get_clients(void);
client_t get_client_by_fd(int fd);
client_list_t get_clients_by_type(enum CLIENT_TYPE type);
void clear_clients(void);
