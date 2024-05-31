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
#include "escaped.h"

void my_error(char *str);
void prepare_exit(int socketFd);
void my_exit(int status);
char *my_strdup(char const *src);
char **str_to_word_array(char *str, char *delim);
int tablen(void **tab);
char *supercat(int n, ...);
char *my_strndup(char const *src, int n);
char *get_current_dir(void);
char *my_snprintf(const char *format, ...);
char *replace_char(char *str, char find, char replace);
void my_exit(int status);
