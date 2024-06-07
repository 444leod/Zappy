/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** supercat
*/

#include "lib.h"
#include "testing.h"

Test(supercat, basic_test)
{
    char *str = supercat(3, "Hello", " ", "World");

    verify_gc(gc_llist(), 1, str);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello World");
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(supercat, empty_test)
{
    char *str = supercat(0);

    verify_gc(gc_llist(), 1, str);
    cr_assert_not_null(str);
    cr_assert_str_empty(str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(supercat, null_test)
{
    char *str = supercat(1, NULL);

    verify_gc(gc_llist(), 1, str);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "");
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(supercat, null_test2)
{
    char *str = supercat(3, "Hello", NULL, " World");

    verify_gc(gc_llist(), 1, str);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello World");
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(supercat, multiple_basic)
{
    char *str = supercat(5, "Hello", " ", "World", " ", "!");

    verify_gc(gc_llist(), 1, str);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello World !");

    char *str2 = supercat(3, "Hello", " ", "World");
    verify_gc(gc_llist(), 2, str, str2);
    cr_assert_not_null(str2);
    cr_assert_str_eq(str2, "Hello World");
    my_free(str);
    verify_gc(gc_llist(), 1, str2);
    my_free(str2);
    verify_gc(gc_llist(), 0);
}
