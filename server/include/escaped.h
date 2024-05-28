/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** escaped
*/

#pragma once

struct special_char_s {
    char str;
    char *escaped;
};

void print_escaped(const char *str);
char *get_escaped_string(const char *str);
