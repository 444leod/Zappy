/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** str_to_word_array
*/

#include "lib.h"
#include "testing.h"

Test(str_to_word_array, basic_string)
{
    const char *str = "Hello World !";
    const char *delim = " ";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "World");
    cr_assert_str_eq(array[2], "!");
    cr_assert_eq(array[3], NULL);
    verify_gc(gc_llist(), 4, array, array[0], array[1], array[2]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
    my_free(array);
    verify_gc(gc_llist(), 0);
}

Test(str_to_word_array, empty_string)
{
    const char *str = "";
    const char *delim = " ";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_empty(array[0]);
    cr_assert_eq(array[1], NULL);
    verify_gc(gc_llist(), 2, array, array[0]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
}

Test(str_to_word_array, empty_delim)
{
    const char *str = "Hello World !";
    const char *delim = "";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_eq(array[0], "Hello World !");
    cr_assert_null(array[1]);
    verify_gc(gc_llist(), 2, array, array[0]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
}

Test(str_to_word_array, multiple_delim)
{
    const char *str = "Hello Wor\tld !";
    const char *delim = " \t";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "Wor");
    cr_assert_str_eq(array[2], "ld");
    cr_assert_str_eq(array[3], "!");
    cr_assert_null(array[4]);
    verify_gc(gc_llist(), 5, array, array[0], array[1], array[2], array[3]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
    my_free(array);
}

Test(str_to_word_array, no_delim_string)
{
    const char *str = "Hello";
    const char *delim = " ";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_null(array[1]);
    verify_gc(gc_llist(), 2, array, array[0]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
}

Test(str_to_word_array, consecutive_delim)
{
    const char *str = "Hello  World !";
    const char *delim = " ";
    char **array = str_to_word_array(str, delim);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "");
    cr_assert_str_eq(array[2], "World");
    cr_assert_str_eq(array[3], "!");
    cr_assert_null(array[4]);
    verify_gc(gc_llist(), 5, array, array[0], array[1], array[2], array[3]);
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    verify_gc(gc_llist(), 1, array);
    my_free(array);
}
