/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** replace_char
*/

#include "testing.h"
#include "lib.h"
#include "garbage_collector.h"

Test(replace_char, basic_test)
{
    char *str = my_strdup("Hello World");

    cr_assert_not_null(str);
    cr_assert_str_eq(replace_char(str, 'o', 'a'), "Hella Warld");
    my_free(str);
}

Test(replace_char, empty_string)
{
    char *str = my_strdup("");

    cr_assert_not_null(str);
    cr_assert_str_eq(replace_char(str, 'o', 'a'), "");
    my_free(str);
}

Test(replace_char, no_char_to_find)
{
    char *str = my_strdup("Hello World");

    cr_assert_not_null(str);
    cr_assert_str_eq(replace_char(str, 'z', 'o'), "Hello World");
    my_free(str);
}

Test(replace_char, null_string)
{
    cr_assert_null(replace_char(NULL, 'z', 'o'));
}

Test(replace_char, advanced_string)
{
    char *str = my_strdup("Hello World");

    cr_assert_not_null(str);
    cr_assert_str_eq(replace_char(str, 'l', 'z'), "Hezzo Worzd");
    my_free(str);
}
