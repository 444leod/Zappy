/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** lib
*/

#pragma once

#include <errno.h>
#include <string.h>
#include <uuid/uuid.h>
#include <stdbool.h>
#include <stdint.h>
#include "escaped.h"

void my_error(const char *str);
void prepare_exit(const int socket_fd);
void my_exit(const int status);
char *my_strdup(const char *src);
char **str_to_word_array(const char *str, const char *delim);
int tablen(const void **tab);
char *supercat(const int n, ...);
char *my_strndup(const char *src, const uint32_t n);
char *get_current_dir(void);
char *my_snprintf(const char *format, ...);
char *replace_char(const char *str, const char find, const char replace);
void my_exit(const int status);
bool is_number(const char *str);
bool is_alphanum(const char *str);
