/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** my_strdup
*/

#include "testing.h"
#include "lib.h"
#include "garbage_collector.h"

Test(my_strdup, basic_test)
{
    char *str = my_strdup("Hello World");

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello World");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strdup, empty_string)
{
    char *str = my_strdup("");

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strdup, null_string)
{
    char *str = my_strdup(NULL);

    cr_assert_null(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strdup, long_string)
{
    char *str = my_strdup("Hello my name is John Doe and I am a software engineer");

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello my name is John Doe and I am a software engineer");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strdup, special_chars)
{
    char *str = my_strdup("Hello my name is John Doe and I am a software engineer !@#$%^&*()");

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello my name is John Doe and I am a software engineer !@#$%^&*()");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strdup, multiple_strings)
{
    char *str1 = my_strdup("Hello world");
    cr_assert_not_null(str1);
    cr_assert_str_eq(str1, "Hello world");
    verify_gc(gc_llist(), 1, str1);

    char *str2 = my_strdup("Hello world");
    cr_assert_not_null(str2);
    cr_assert_str_eq(str2, "Hello world");
    verify_gc(gc_llist(), 2, str1, str2);

    my_free(str1);
    verify_gc(gc_llist(), 1, str2);
    my_free(str2);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, basic_test)
{
    char *str = my_strndup("Hello World", 5);

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, empty_string)
{
    char *str = my_strndup("", 5);

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, null_string)
{
    char *str = my_strndup(NULL, 5);

    cr_assert_null(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, long_string)
{
    char *str = my_strndup("Hello my name is John Doe and I am a software engineer", 10);

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello my n");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, special_chars)
{
    char *str = my_strndup("Hello my name is John Doe and I am a software engineer !@#$%^&*()", 10);

    cr_assert_not_null(str);
    cr_assert_str_eq(str, "Hello my n");
    verify_gc(gc_llist(), 1, str);
    my_free(str);
    verify_gc(gc_llist(), 0);
}

Test(my_strndup, multiple_strings)
{
    char *str1 = my_strndup("Hello world", 5);
    cr_assert_not_null(str1);
    cr_assert_str_eq(str1, "Hello");
    verify_gc(gc_llist(), 1, str1);

    char *str2 = my_strndup("Hello world", 5);
    cr_assert_not_null(str2);
    cr_assert_str_eq(str2, "Hello");
    verify_gc(gc_llist(), 2, str1, str2);

    my_free(str1);
    verify_gc(gc_llist(), 1, str2);
    my_free(str2);
    verify_gc(gc_llist(), 0);
}
