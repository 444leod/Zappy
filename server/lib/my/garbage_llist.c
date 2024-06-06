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
 * @return gc_node_t* the garbage collector linked list
*/
gc_node_t *gc_llist(void)
{
    static gc_node_t llist = NULL;

    return &llist;
}
