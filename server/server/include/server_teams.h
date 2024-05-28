/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** teams
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
#include "clientllist.h"
#include "debug.h"
#include "garbage_collector.h"
#include "macros.h"

typedef struct server_info_s {
    int port;
    char *path;
    char *ip;
} *server_info_t;

enum CONTEXT {
    GLOBAL_CONTEXT,
    TEAM_CONTEXT,
    CHANNEL_CONTEXT,
    THREAD_CONTEXT,
};

int server(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port, char **ip);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void reply_code(client_t client);
void special_print(fd_set *readfds, fd_set *writefds);
void loop_clients(client_t *clients, fd_set *readfds,
    fd_set *writefds, server_info_t server_info);
void handle_command(client_t client);
void get_port(int fd, int *port);
void send_packet_to_logged_users(packet_t *packet, client_t client);
void send_packet_to_client(client_t client, packet_t *packet);
void send_packet_to_clients(clients_t clients, packet_t *packet);
enum CONTEXT get_current_context(client_t client);
bool is_context_valid(client_t client, bool need_subscription);
