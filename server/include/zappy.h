/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Zappy
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "lib.h"
#include "clients.h"
#include "debug.h"
#include "garbage_collector.h"
#include "macros.h"

typedef struct team_name_s {
    struct team_name_s *next;
    char *name;
} *team_name_t;

typedef struct server_info_s {
    int port;
    uint32_t clientsNb;
    uint32_t freq;
    uint32_t width;
    uint32_t height;
    team_name_t team_names;
} *server_info_t;



int server(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void send_packets(client_t client);
void special_print(fd_set *readfds, fd_set *writefds);
void loop_clients(client_t *clients, fd_set *readfds,
    fd_set *writefds);
void handle_command(client_t client);
void get_port(int fd, int *port);
void queue_packet_to_client_type(enum CLIENT_TYPE type, packet_t *packet);
void check_args(int argc, char *argv[]);
server_info_t init_server_info(char *argv[]);
void display_help(char *str);
