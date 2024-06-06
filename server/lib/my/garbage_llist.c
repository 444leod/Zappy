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
    g_llist_t newNode = malloc(sizeof(garbage_t));

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
 * @return g_llist_t the new list
*/
g_llist_t g_insert_end(void *data, g_llist_t list)
{
    g_llist_t newNode = g_create(data);

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
