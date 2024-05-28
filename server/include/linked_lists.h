/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** linked_lists
*/

#pragma once

#include <uuid/uuid.h>
#include <time.h>

typedef struct node_s {
    struct node_s *next;
    void *data;
} *node_t;

void add_to_list(void *new_data, node_t *list);
void remove_from_list(void *data, node_t *list);
