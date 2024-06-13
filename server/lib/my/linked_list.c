/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_to_list
*/

#include "linked_lists.h"
#include "garbage_collector.h"

/**
 * @brief Add a node to a list
 * @details Add a node to a list with the given pointer as its data
 *
 * @param newData the pointer of the node data
 * @param list the list
*/
void add_to_list(void *newData, node_t *list)
{
    node_t new_node = my_malloc(sizeof(struct node_s));
    node_t tmp = *list;

    new_node->data = newData;
    new_node->next = NULL;
    if (list == NULL || *list == NULL) {
        *list = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}

/**
 * @brief Remove a node from a list
 * @details Remove a node from a list based on the given pointer
 *
 * @param data the pointer to the node to remove
 * @param list the list
*/
void remove_from_list(void *data, node_t *list)
{
    node_t tmp = *list;
    node_t prev = NULL;

    if (tmp && tmp->data == data) {
        *list = tmp->next;
        if (tmp->next)
            tmp->next->prev = NULL;
        my_free(tmp);
        return;
    }
    while (tmp && tmp->data != data) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
        return;
    prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = prev;
    my_free(tmp);
}

/**
 * @brief Get the node at the given index
 * @details Get the node at the given index
 *
 * @param index the index of the data to get
 * @param list the list
 *
 * @return node_t the data
*/
node_t get_node_by_index(const int index, const node_t list)
{
    node_t tmp = list;
    int i = 0;

    if (index < 0)
        return (NULL);
    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }
    if (i != index)
        return (NULL);
    return (tmp);
}

/**
 * @brief Get the size of a linked list
 * @details Get the size of a linked list
 *
 * @param list the list
 *
 * @return uint32_t the size of the list
*/
uint32_t get_list_size(const node_t list)
{
    node_t tmp = list;
    uint32_t i = 0;

    while (tmp) {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

/**
 * @brief Get the index of a node in a list
 * @details Get the index of a node in a list
 *
 * @param data the pointer to the node to get the index of
 * @param list the list
 *
 * @return int the index of the node (-1 if not found)
*/
int get_node_index(void *data, node_t list)
{
    node_t tmp = list;
    int i = 1;

    if (!tmp)
        return (-1);
    if (tmp->next == list && tmp->data != data)
        return (-1);
    if (tmp->data == data)
        return (0);
    tmp = tmp->next;
    while (tmp && tmp->data != data && tmp != list) {
        tmp = tmp->next;
        i++;
    }
    if (!tmp || tmp->data != data)
        return (-1);
    return (i);
}
