/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** commands
*/

#pragma once

#include "server_info.h"
#include "clients.h"

char *get_tile_content_string(const tile_t tile, const position_t position);
void send_tile_content_to_client(const client_t client,
    const server_info_t serverInfo, const position_t position);
void sent_tile_content_to_client_list(const client_list_t clients,
    const server_info_t serverInfo, const position_t position);

char *get_map_content_string(const server_info_t server_info);
void send_map_content_to_client(const client_t client,
    const server_info_t server_info);
void send_map_content_to_client_list(const client_list_t clients,
    const server_info_t server_info);

char *get_player_inventory_string(const player_t player);
void send_player_inventory_to_client(const client_t client,
    const int playerNumber);
void send_player_inventory_to_client_list(const client_list_t clients,
    const int playerNumber);

char *get_player_level_string(const player_t player);
void send_player_level_to_client(const client_t client, const int playerNumber);
void send_player_level_to_client_list(const client_list_t clients,
    const int playerNumber);

char *get_map_size_string(const server_info_t server_info);
void send_map_size_to_client(const client_t client,
    const server_info_t server_info);
void send_map_size_to_client_list(const client_list_t clients,
    const server_info_t server_info);

char *get_player_pos_string(const player_t player);
void send_player_pos_to_client_list(const client_list_t clients,
    const int playerNumber);
void send_player_pos_to_client(const client_t client, const int playerNumber);

char *get_time_unit_string(const server_info_t server_info);
void send_time_unit_to_client(const client_t client,
    const server_info_t server_info);
void send_time_unit_to_client_list(const client_list_t clients,
    const server_info_t server_info);

char *get_time_unit_modification_string(int time_unit);
void send_time_unit_modification_to_client(const client_t client,
    int time_unit);
void send_time_unit_modification_to_client_list(const client_list_t clients,
    int time_unit);

char *get_team_name_string(const team_t team);
char *get_team_name_list_string(const team_list_t teams);
void send_team_name_list_to_client(const client_t client, const team_t team);
void send_team_name_list_to_client_list(const client_list_t clients,
    const team_t team);



