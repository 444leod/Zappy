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
#include "server_info.h"
#include "clients.h"

int server(const int argc, const char *argv[]);
void check_args(const int argc, const char *argv[]);
int get_socket(void);
void bind_socket(const int socketFd, const uint16_t port);
void listen_socket(const int socketFd, const int maxClients);
void accept_socket(const int socketFd, void (*func)(int));
void send_packets(client_t client);
void special_print(const fd_set *readfds, const fd_set *writefds);
void loop_clients(const client_list_t clients, const fd_set *readfds,
    const fd_set *writefds, const server_info_t serverInfo);
void handle_command(const client_t client, const server_info_t serverInfo);
void get_port(const int fd, const int *port);
void queue_packet_to_client_type(const enum CLIENT_TYPE type,
    packet_t *packet);
server_info_t init_server_info(const char *argv[]);
void display_help(const char *str);
void queue_buffer(const client_t client, const char *buffer);
void select_wrapper(int *max_sd, fd_set *readfds,
    fd_set *writefds, client_list_t clients);
void read_buffer(const client_t client);
void check_player_death(const client_t client,
    const map_t map, const uint32_t frequency);
