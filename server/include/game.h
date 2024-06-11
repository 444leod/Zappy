/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include <stdint.h>
#include <time.h>
#include <uuid/uuid.h>
#include "teams.h"

#define D_FOOD 0.5
#define D_LINEMATE 0.3
#define D_DERAUMERE 0.15
#define D_SIBUR 0.1
#define D_MENDIANE 0.1
#define D_PHIRAS 0.08
#define D_THYSTAME 0.05

enum ORIENTATION {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct rocks_s {
    uint32_t linemate;
    uint32_t deraumere;
    uint32_t sibur;
    uint32_t mendiane;
    uint32_t phiras;
    uint32_t thystame;
} rocks_t;

typedef struct player_s {
    uuid_t id;
    team_t team;
    position_t position;
    int level;
    rocks_t rocks;
    uint32_t food;
    enum ORIENTATION orientation;
    clock_t lastFoodEatenTime;
} * player_t;

typedef struct player_list_s {
    struct player_list_s *next;
    struct player_list_s *prev;
    player_t player;
} * player_list_t;

typedef struct egg_s {
    position_t pos;
    team_t team;
} * egg_t;

typedef struct egg_list_s {
    struct egg_list_s *next;
    struct egg_list_s *prev;
    egg_t egg;
} * egg_list_t;

typedef struct tile_s {
    rocks_t rocks;
    uint32_t food;
    player_list_t players;
    egg_list_t eggs;
} * tile_t;

typedef struct tile_list_s {
    struct tile_list_s *next;
    struct tile_list_s *prev;
    tile_t tile;
} * tile_list_t;

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

map_t create_map(uint32_t width, uint32_t height);
void init_map(map_t map, team_list_t teams);
tile_t get_tile_at_position(position_t position, map_t map);
void add_player_at_position(player_t player, position_t position, map_t map);
void move_player(player_t player, position_t position, map_t map);
void add_egg_at_position(const team_t, const position_t, map_t);
egg_list_t get_team_eggs(const team_t team, const map_t map);
egg_t get_random_egg(const team_t team, map_t map);
player_t egg_to_player(egg_t egg, map_t map);