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

void init(void);
void assert_stdout_eq_str(char *str);
void verify_gc(gc_node_t *list, uint32_t size, ...);
