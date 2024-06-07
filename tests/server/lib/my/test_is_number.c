/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_number
*/

#include "testing.h"
#include "lib.h"

Test(is_number, basic_string1)
{
    cr_assert_eq(is_number("123"), true);
}

Test(is_number, basic_string2)
{
    cr_assert_eq(is_number("1234567890"), true);
}

Test(is_number, basic_string3)
{
    cr_assert_eq(is_number("1234567890-"), false);
}

Test(is_number, basic_string4)
{
    cr_assert_eq(is_number("1234567890+"), false);
}

Test(is_number, advanced_string1)
{
    cr_assert_eq(is_number("1234567890-+"), false);
}

Test(is_number, empty_string)
{
    cr_assert_eq(is_number(""), false);
}

Test(is_number, whitespace_string)
{
    cr_assert_eq(is_number(" "), false);
}

Test(is_number, alphanumeric_string)
{
    cr_assert_eq(is_number("HelloWorld123"), false);
}

Test(is_number, positive_number)
{
    cr_assert_eq(is_number("+123"), true);
}

Test(is_number, negative_number)
{
    cr_assert_eq(is_number("-123"), true);
}
