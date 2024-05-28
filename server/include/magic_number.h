/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** magic_number
*/

#pragma once

#include <stdbool.h>

#define MAGIC_NUMBER 0xdeadbeef

bool is_magic_number_valid(int fd);
void write_magic_number(int fd);
