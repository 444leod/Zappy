/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** garbage_collector
*/

#include "testing.h"
#include "garbage_collector.h"

void verify_garbage_collector_list(gc_node_t *list, uint32_t size, ...)
{
    va_list ap;

    cr_assert_not_null(list);
    gc_node_t temp = *list;
    gc_node_t first;
    cr_assert_not_null(temp);
    va_start(ap, size);
    for (uint32_t i = 0; i < size; i++) {
        if (i == 0)
            first = temp;
        cr_assert_not_null(temp);
        cr_assert_eq(temp->data, va_arg(ap, void *));
        temp = temp->next;
    }
    va_end(ap);
    cr_assert_eq(temp, first);
}

Test(garbage_collector, malloc_and_free)
{
    char *ptr = my_malloc(10);
    cr_assert_not_null(ptr);
    verify_garbage_collector_list(gc_llist(), 1, ptr);

    for (int i = 0; i < 10; i++)
        cr_assert_eq(ptr[i], 0);

    my_free(ptr);
    cr_assert_null(*gc_llist());
}

Test(garbage_collector, malloc_and_free_multiple)
{
    char *ptr = my_malloc(10);
    cr_assert_not_null(ptr);
    verify_garbage_collector_list(gc_llist(), 1, ptr);

    char *ptr2 = my_malloc(10);
    cr_assert_not_null(ptr2);
    verify_garbage_collector_list(gc_llist(), 2, ptr, ptr2);

    for (int i = 0; i < 10; i++) {
        cr_assert_eq(ptr[i], 0);
        cr_assert_eq(ptr2[i], 0);
    }

    my_free(ptr);
    verify_garbage_collector_list(gc_llist(), 1, ptr2);

    my_free(ptr2);
    cr_assert_null(*gc_llist());
}

Test(garbage_collector, realloc)
{
    char *ptr = my_malloc(10);
    cr_assert_not_null(ptr);
    verify_garbage_collector_list(gc_llist(), 1, ptr);

    for (int i = 0; i < 10; i++)
        cr_assert_eq(ptr[i], 0);

    ptr = my_realloc(ptr, 20, 10);
    cr_assert_not_null(ptr);
    verify_garbage_collector_list(gc_llist(), 1, ptr);

    for (int i = 0; i < 20; i++)
        cr_assert_eq(ptr[i], 0);

    my_free(ptr);
    cr_assert_null(*gc_llist());
}
