/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** linked_list
*/

#include "testing.h"
#include "linked_lists.h"

Test(linked_list, add_to_list)
{
    node_t list = NULL;
    int data = 42;

    add_to_list(&data, &list);
    cr_assert_not_null(list);
    cr_assert_eq(*(int *)list->data, 42);
    cr_assert_null(list->next);
}

Test(linked_list, add_to_list_multiple)
{
    node_t list = NULL;
    int data1 = 42;
    int data2 = 84;

    add_to_list(&data1, &list);
    add_to_list(&data2, &list);
    cr_assert_not_null(list);
    cr_assert_eq(*(int *)list->data, 42);
    cr_assert_not_null(list->next);
    cr_assert_eq(*(int *)list->next->data, 84);
    cr_assert_null(list->next->next);
}

Test(linked_list, remove_from_list)
{
    node_t list = NULL;
    int data = 42;

    add_to_list(&data, &list);
    remove_from_list(&data, &list);
    cr_assert_null(list);
}

Test(linked_list, remove_from_list_multiple)
{
    node_t list = NULL;
    int data1 = 42;
    int data2 = 84;

    add_to_list(&data1, &list);
    add_to_list(&data2, &list);
    remove_from_list(&data1, &list);
    cr_assert_not_null(list);
    cr_assert_eq(*(int *)list->data, 84);
    cr_assert_null(list->next);
}

Test(linked_list, remove_from_list_not_found)
{
    node_t list = NULL;
    int data1 = 42;
    int data2 = 84;

    add_to_list(&data1, &list);
    remove_from_list(&data2, &list);
    cr_assert_not_null(list);
    cr_assert_eq(*(int *)list->data, 42);
    cr_assert_null(list->next);
}

Test(linked_list, get_node_by_index)
{
    node_t list = NULL;
    int data1 = 42;
    int data2 = 84;

    add_to_list(&data1, &list);
    add_to_list(&data2, &list);
    cr_assert_eq(*(int *)get_node_by_index(0, list)->data, 42);
    cr_assert_eq(*(int *)get_node_by_index(1, list)->data, 84);
    cr_assert_null(get_node_by_index(2, list));
}

Test(linked_list, get_list_size)
{
    node_t list = NULL;
    int data1 = 42;
    int data2 = 84;

    add_to_list(&data1, &list);
    add_to_list(&data2, &list);
    cr_assert_eq(get_list_size(list), 2);
}

Test(linked_list, get_list_size_empty)
{
    node_t list = NULL;

    cr_assert_eq(get_list_size(list), 0);
}

Test(linked_list, get_list_size_single)
{
    node_t list = NULL;
    int data = 42;

    add_to_list(&data, &list);
    cr_assert_eq(get_list_size(list), 1);
}
