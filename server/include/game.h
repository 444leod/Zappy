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
#include <stdbool.h>
#include "teams.h"

#define DEATH_TICKS 126
#define REFILL_TICKS 10

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
    bool isDead;
    uuid_t id;
    uint32_t player_number;
    uint32_t egg_number;
    team_t team;
    position_t position;
    uint8_t level;
    rocks_t rocks;
    uint32_t food;
    enum ORIENTATION orientation;
    struct timespec last_eat_check_time;
    double death_remaining_time;
    struct timespec last_stuck_check;
    double stun_time;
    uint32_t ritual_id;
} * player_t;

typedef struct player_list_s {
    struct player_list_s *next;
    struct player_list_s *prev;
    player_t player;
} * player_list_t;

typedef struct egg_s {
    uint32_t number;
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

typedef struct pickup_command_s {
    const char *key;
    bool (*pick_func)(player_t, tile_t, int8_t);
} pickup_command_t;

map_t create_map(const uint32_t width, const uint32_t height);
void fill_map(const map_t map, rocks_t *current_rocks,
    uint32_t *current_food, team_list_t teams);
tile_t get_tile_at_position(const position_t position, const map_t map);
void add_player_at_position(const player_t player, const position_t position,
    const map_t map);
void move_player(const player_t player, const position_t position,
    const map_t map);
void add_egg_at_position(const team_t, const position_t, map_t);
egg_list_t get_team_eggs(const team_t team, const map_t map);
egg_t get_random_egg(const team_t team, map_t map);
player_t egg_to_player(egg_t egg, map_t map);
bool player_pick_up(
    const char *key, player_t player, tile_t tile, int8_t delta);
void remove_player(const player_t player, const map_t map);
