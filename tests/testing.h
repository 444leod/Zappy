/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** testing
*/

#pragma once

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "garbage_collector.h"

int init(void);
void verify_gc(gc_node_t *list, uint32_t size, ...);
