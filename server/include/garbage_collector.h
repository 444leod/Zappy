/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** garbage
*/
    #pragma once

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <unistd.h>
    #include <stdint.h>

typedef struct gc_node_s {
    void *data;
    struct gc_node_s *next;
    struct gc_node_s *prev;
} *gc_node_t;

gc_node_t *gc_llist(void);
void my_free_all(void);
void my_free(void *pointer);
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size, size_t oldSize);
