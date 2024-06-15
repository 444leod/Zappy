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
 * @brief Create a new node
 * @details Create a new node with the given data (a ptr)
 *
 * @param data the data to store in the node (a ptr)
 *
 * @return gc_node_t the new node
*/
static gc_node_t gc_create(void *data)
{
    gc_node_t newNode = malloc(sizeof(struct gc_node_s));

    if (newNode == NULL)
        return NULL;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/**
 * @brief Insert a new node at the end of the list
 * @details Insert a new node at the end of the list
 *
 * @param data the data to store in the new node
 * @param list the list to insert the new node in
 *
 * @return gc_node_t the new list
*/
static gc_node_t gc_insert_end(void *data, gc_node_t list)
{
    gc_node_t newNode = gc_create(data);

    if (newNode == NULL)
        return NULL;
    if (list == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list = newNode;
        return list;
    }
    list->prev->next = newNode;
    newNode->prev = list->prev;
    newNode->next = list;
    list->prev = newNode;
    return list;
}

/**
 * @brief Delete the first node of the list
 * @details Delete the first node of the list
 *
 * @param list the list to delete the first node from
 *
 * @return gc_node_t the new list
*/
static gc_node_t gc_delete_begin(gc_node_t list)
{
    gc_node_t temp;

    if (list == NULL)
        return list;
    else if (list->next == list) {
        free(list->data);
        free(list);
        list = NULL;
        return list;
    }
    temp = list;
    list->prev->next = list->next;
    list->next->prev = list->prev;
    list = list->next;
    free(temp->data);
    free(temp);
    temp = NULL;
    return list;
}

/**
 * @brief Malloc wrapper with garbage collector
 * @details Malloc wrapper with garbage collector, store malloced pointers in a
 * linked list
 *
 * @param size the size of the memory to allocate
 *
 * @return void* the pointer to the allocated memory
*/
void *my_malloc(const size_t size)
{
    void *variable = malloc(size);
    gc_node_t *llist = gc_llist();

    if (variable == NULL)
        my_error("Malloc failed");
    memset(variable, 0, size);
    *llist = gc_insert_end(variable, *llist);
    if (*llist == NULL)
        my_error("Malloc failed");
    return variable;
}

/**
 * @brief Try to free first or last node of the list (faster)
 * @details Try to free first or last node of the list (faster)
 *
 * @param pointer the pointer to free
 * @param gc the linked list
 *
 * @return bool true if the pointer was freed, false otherwise
 */
static bool try_free_special_cases(void *pointer, gc_node_t *gc)
{
    if ((*gc)->data == pointer) {
        *gc = gc_delete_begin(*gc);
        return true;
    }
    if ((*gc)->prev->data == pointer) {
        *gc = gc_delete_begin((*gc)->prev)->next;
        return true;
    }
    return false;
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
    gc_node_t *llist = gc_llist();
    gc_node_t temp;

    if (!*llist)
        return;
    if (try_free_special_cases(pointer, llist))
        return;
    temp = (*llist)->next;
    while (temp != *llist) {
        if (temp->data == pointer) {
            temp = gc_delete_begin(temp);
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
    gc_node_t *llist = gc_llist();

    while (*llist)
        *llist = gc_delete_begin(*llist);
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
void *force_malloc(const size_t size)
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
 * @param oldSize the old size of the memory
 *
 * @return void* the pointer to the allocated memory
*/
void *my_realloc(void *ptr, const size_t size, const size_t oldSize)
{
    void *variable = my_malloc(size);

    memcpy(variable, ptr, oldSize);
    my_free(ptr);
    return variable;
}
