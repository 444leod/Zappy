/*
** EPITECH PROJECT, 2023
** garbage_collector
** File description:
** garbage_collector
*/

#include "garbage_collector.h"
#include "lib.h"
#include <unistd.h>

/**
 * @brief Malloc wrapper with garbage collector
 * @details Malloc wrapper with garbage collector, store malloced pointers in a
 * linked list
 *
 * @param size the size of the memory to allocate
 *
 * @return void* the pointer to the allocated memory
*/
void *my_malloc(size_t size)
{
    void *variable = malloc(size);
    g_llist_t *llist = get_llist();

    if (variable == NULL)
        my_error("Malloc failed");
    memset(variable, 0, size);
    *llist = g_insert_end(variable, *llist);
    if (*llist == NULL)
        my_error("Malloc failed");
    return variable;
}

/**
 * @brief Free wrapper with garbage collector
 * @details Free wrapper with garbage collector, free the pointer and remove it
 * from the linked list
 *
 * @param pointer the pointer to free
*/
void my_free(void *pointer)
{
    g_llist_t *llist = get_llist();
    g_llist_t temp;

    if ((*llist)->data == pointer) {
        *llist = g_delete_begin(*llist);
        return;
    }
    temp = (*llist)->next;
    while (temp != *llist) {
        if (temp->data == pointer) {
            temp = g_delete_begin(temp);
            return;
        }
        temp = temp->next;
    }
    free(pointer);
}

/**
 * @brief Free all the pointers in the linked list
*/
void my_free_all(void)
{
    g_llist_t *llist = get_llist();

    while (*llist)
        *llist = g_delete_begin(*llist);
}

/**
 * @brief Malloc wrapper (no garbage collector)
 * @details Malloc wrapper (no garbage collector), if malloc failed, exit the
 * program
 *
 * @param size the size of the memory to allocate
 *
 * @return void* the pointer to the allocated memory
*/
void *force_malloc(size_t size)
{
    void *variable = malloc(size);

    if (variable == NULL)
        my_error("Malloc failed");
    return variable;
}

/**
 * @brief Realloc wrapper with garbage collector
 * @details Realloc wrapper with garbage collector, realloc the pointer and
 * update it in the linked list
 *
 * @param ptr the pointer to realloc
 * @param size the size of the memory to allocate
 * @param old_size the old size of the memory
 *
 * @return void* the pointer to the allocated memory
*/
void *my_realloc(void *ptr, size_t size, size_t old_size)
{
    void *variable = my_malloc(size);

    memcpy(variable, ptr, old_size);
    my_free(ptr);
    return variable;
}
