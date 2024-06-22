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
#include "select_wrapper.h"

int server(const int argc, const char *argv[]);
void check_args(const int argc, const char *argv[]);
int get_socket(void);
void bind_socket(const int socket_fd, const uint16_t port);
void listen_socket(const int socket_fd, const int max_clients);
void accept_socket(const int socket_fd, void (*func)(int));
void send_packets(client_t client);
void special_print(const fd_set *readfds, const fd_set *writefds);
void loop_clients(const client_list_t clients, const fd_set *readfds,
    const fd_set *writefds, const server_info_t server_info);
void handle_command(const client_t client, const server_info_t server_info);
void get_port(const int fd, const int *port);
void queue_packet_to_client_type(const enum CLIENT_TYPE type,
    packet_t *packet);
void queue_packet_to_player(player_t player, packet_t *packet);
void prepend_client_command(client_t client, client_command_t command);
server_info_t init_server_info(const char *argv[]);
void display_help(const char *str);
void queue_buffer(const client_t client, const char *buffer);
void select_wrapper(select_data_t *select_data, client_list_t clients,
    const server_info_t server_info);
void read_buffer(const client_t client);
void check_player_death(const client_t client,
    const map_t map, const uint32_t frequency);
bool can_interact(client_t client);
void refill_map(const server_info_t server_info);
void change_map_ressource(
    const char *key, const server_info_t server_info, int8_t delta);
char **parse_command_args(const char *command);
void init_map(const server_info_t server_info);
