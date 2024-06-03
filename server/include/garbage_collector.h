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

struct garbagec_t {
    void *data;
    struct garbagec_t *next;
    struct garbagec_t *prev;
};

typedef struct garbagec_t garbage_t;
typedef garbage_t *g_llist_t;
g_llist_t g_create(void *data);
g_llist_t g_delete_begin(g_llist_t list);
g_llist_t g_insert_end(void *data, g_llist_t list);
g_llist_t *get_llist(void);
void my_free_all(void);
void my_free(void *pointer);
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size, size_t old_size);
