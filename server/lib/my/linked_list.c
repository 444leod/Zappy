/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_to_list
*/

#include "linked_lists.h"
#include "garbage_collector.h"

void add_to_list(void *new_data, node_t *list)
{
    node_t new_node = my_malloc(sizeof(struct node_s));
    node_t tmp = *list;

    new_node->data = new_data;
    new_node->next = NULL;
    if (list == NULL || *list == NULL) {
        *list = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
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
    my_free(tmp);
}

/**
 * @brief Get the data from a list based on the index
 * @details Get the data from a list based on the index
 *
 * @param index the index of the data to get
 * @param list the list
 *
 * @return void* the data
*/
void *get_data_by_index(int index, node_t list)
{
    node_t tmp = list;
    int i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }
    if (i != index)
        return (NULL);
    return (tmp->data);
}
