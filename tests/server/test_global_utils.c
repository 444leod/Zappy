/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sample
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "garbage_collector.h"

void init(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void verify_gc(gc_node_t *list, uint32_t size, ...)
{
    cr_assert_not_null(list);

    if (size == 0) {
        cr_assert_null(*list);
        return;
    } else
        cr_assert_not_null(*list);

    va_list ap;
    va_start(ap, size);

    gc_node_t tmp = *list;
    gc_node_t first;

    for (uint32_t i = 0; i < size; i++) {
        if (i == 0)
            first = tmp;
        cr_assert_not_null(tmp);
        cr_assert_eq(tmp->data, va_arg(ap, void *));
        tmp = tmp->next;
    }
    cr_assert_eq(tmp, first);
    va_end(ap);
}

void assert_stdout_eq_str(char *str)
{
    fflush(stdout);
    cr_assert_stdout_eq_str(str);
}

/**
 * A boolean assertion example.
 * You can simply check equalities this way.
*/
Test(example_suite, assert_example_one) {
    cr_assert(0 == 0);
}

/**
 * A typed assertion example.
 * If you don't want to write `==`,
 * then you can call `..._eq`.
*/
Test(example_suite, assert_eq_example) {
    cr_assert_eq(0, 0);
}

/**
 * An assertion example based on program output.
 * Uses `.init` to setup the redirection of standard outputs.
*/
Test(example_suite, stdout_example, .init=init) {
    write(1, "Hello!", 6);
    cr_assert_stdout_eq_str("Hello!");
}
