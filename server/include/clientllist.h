/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clientllist
*/

#pragma once

#include <stdlib.h>
#include <uuid/uuid.h>
#include "packet.h"
#include "linked_lists.h"

enum CLIENT_TYPE {
    NONE,
    GRAPHICAL,
    AI,
    ADMIN
};

typedef struct client_s {
    int fd;
    char *team;
    int client_num;
    packet_queue_t packet_queue;
    enum CLIENT_TYPE type;
    char *command;
    char *next_commands;
    unsigned int data_len;
    enum {
        READING,
        PROCESSING,
    } data_status;
    struct client_s *next;
} *client_t;

typedef struct clients_s {
    struct clients_s *next;
    client_t client;
} *clients_t;

void add_client(client_t new_client);
void remove_client(int fd);
client_t create_client(int fd);
client_t *get_clients(void);
client_t get_client_by_fd(int fd);
clients_t get_clients_by_type(enum CLIENT_TYPE type);
void clear_clients(void);
