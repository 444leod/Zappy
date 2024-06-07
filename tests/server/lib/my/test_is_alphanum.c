/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_alphanum
*/

#include "testing.h"
#include "lib.h"

Test(is_alphanum, basic_string1)
{
    cr_assert_eq(is_alphanum("HelloWorld"), true);
}

Test(is_alphanum, basic_string2)
{
    cr_assert_eq(is_alphanum("HelloWorld123"), true);
}

Test(is_alphanum, basic_string3)
{
    cr_assert_eq(is_alphanum("HelloWorld123!"), false);
}

Test(is_alphanum, basic_string4)
{
    cr_assert_eq(is_alphanum("HelloWorld123!@#"), false);
}

Test(is_alphanum, advanced_string1)
{
    cr_assert_eq(is_alphanum("H3ll0World! Th1s 5tring l°°ks weird"), false);
}

Test(is_alphanum, empty_string)
{
    cr_assert_eq(is_alphanum(""), true);
}

Test(is_alphanum, whitespace_string)
{
    cr_assert_eq(is_alphanum(" "), false);
}

Test(is_alphanum, alphanumeric_with_spaces)
{
    cr_assert_eq(is_alphanum("Hello World 123"), false);
}

Test(is_alphanum, alphanumeric_with_underscore)
{
    cr_assert_eq(is_alphanum("Hello_World_123"), false);
}

Test(is_alphanum, alphanumeric_with_dash)
{
    cr_assert_eq(is_alphanum("Hello-World-123"), false);
}

Test(is_alphanum, string_with_tab)
{
    cr_assert_eq(is_alphanum("Hello\tWorld123"), false);
}

Test(is_alphanum, string_with_newline)
{
    cr_assert_eq(is_alphanum("Hello\nWorld123"), false);
}
