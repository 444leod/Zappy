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

typedef struct client_s {
    int fd;
    char *team;
    uint16_t clientNumber;
    packet_queue_t packetQueue;
    enum CLIENT_TYPE type;
    client_command_list_t commands;
    char *buffer;
    struct client_s *next;
} *client_t;

typedef struct clients_s {
    struct clients_s *next;
    client_t client;
} *clients_t;

void add_client(client_t client);
void remove_client(int fd);
client_t create_client(int fd);
client_t *get_clients(void);
client_t get_client_by_fd(int fd);
clients_t get_clients_by_type(enum CLIENT_TYPE type);
void clear_clients(void);
