/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include <stdint.h>
#include <time.h>
#include "teams.h"

enum ORIENTATION {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

typedef struct rocks_s {
    uint32_t linemate;
    uint32_t deraumere;
    uint32_t sibur;
    uint32_t mendiane;
    uint32_t phiras;
    uint32_t thystame;
} rocks_t;

typedef struct player_s {
    int id;
    team_t *team;
    int x;
    int y;
    int level;
    rocks_t rocks;
    uint32_t food;
    enum ORIENTATION orientation;
    clock_t lastFoodEatenTime;
} player_t;

typedef struct player_list_s {
    struct player_list_s *next;
    struct player_list_s *prev;
    player_t *player;
} * player_list_t;

typedef struct tile_s {
    rocks_t rocks;
    uint32_t food;
    player_list_t players;
} * tile_t;

typedef struct tile_list_s {
    struct tile_list_s *next;
    struct tile_list_s *prev;
    tile_t tile;
} *tile_list_t;

typedef struct line_s {
    tile_list_t tile_list;
} * line_t;

typedef struct line_list_s {
    struct line_list_s *next;
    struct line_list_s *prev;
    line_t line;
} * line_list_t;

typedef struct map_s {
    line_list_t line_list;
    uint32_t width;
    uint32_t height;
} * map_t;

typedef struct position_s {
    int x;
    int y;
} position_t;

map_t create_map(uint32_t width, uint32_t height);
tile_t get_tile_at_position(position_t position, map_t map);
void add_player_at_position(player_t *player, position_t position, map_t map);
void move_player(player_t *player, position_t position, map_t map);
position_t get_player_position(player_t *player, map_t map);
