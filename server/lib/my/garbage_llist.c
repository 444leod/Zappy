/*
** EPITECH PROJECT, 2023
** garbage_collector
** File description:
** garbage_llist
*/

#include "garbage_collector.h"

/**
 * @brief Get the garbage collector linked list
 *
 * @return g_llist_t* the garbage collector linked list
*/
g_llist_t *get_llist(void)
{
    static g_llist_t llist = NULL;

    return &llist;
}

/**
 * @brief Create a new node
 * @details Create a new node with the given data (a ptr)
 *
 * @param data the data to store in the node (a ptr)
 *
 * @return g_llist_t the new node
*/
g_llist_t g_create(void *data)
{
    g_llist_t new_node = malloc(sizeof(garbage_t));

    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/**
 * @brief Insert a new node at the end of the list
 * @details Insert a new node at the end of the list
 *
 * @param data the data to store in the new node
 * @param list the list to insert the new node in
 *
 * @return g_llist_t the new list
*/
g_llist_t g_insert_end(void *data, g_llist_t list)
{
    g_llist_t new_node = g_create(data);

    if (new_node == NULL)
        return NULL;
    if (list == NULL) {
        new_node->next = new_node;
        new_node->prev = new_node;
        list = new_node;
        return list;
    }
    list->prev->next = new_node;
    new_node->prev = list->prev;
    new_node->next = list;
    list->prev = new_node;
    return list;
}

/**
 * @brief Delete the first node of the list
 * @details Delete the first node of the list
 *
 * @param list the list to delete the first node from
 *
 * @return g_llist_t the new list
*/
g_llist_t g_delete_begin(g_llist_t list)
{
    g_llist_t temp;

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
