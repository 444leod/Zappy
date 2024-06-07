/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** my_snprintf
*/

#include "testing.h"
#include "lib.h"
#include <limits.h>

Test(my_snprintf, basic_string1)
{
    char *str = my_snprintf("Hello World");

    cr_assert_str_eq(str, "Hello World");
}

Test(my_snprintf, basic_string2)
{
    char *str = my_snprintf("Hello %s", "World");

    cr_assert_str_eq(str, "Hello World");
}

Test(my_snprintf, integer_format)
{
    char *str = my_snprintf("%d", 123);
    cr_assert_str_eq(str, "123");
}

Test(my_snprintf, negative_integer_format)
{
    char *str = my_snprintf("%d", -123);
    cr_assert_str_eq(str, "-123");
}

Test(my_snprintf, float_format)
{
    char *str = my_snprintf("%.2f", 123.45);
    cr_assert_str_eq(str, "123.45");
}

Test(my_snprintf, character_format)
{
    char *str = my_snprintf("%c", 'A');
    cr_assert_str_eq(str, "A");
}

Test(my_snprintf, string_format)
{
    char *str = my_snprintf("%s", "Hello World");
    cr_assert_str_eq(str, "Hello World");
}

Test(my_snprintf, multiple_format_specifiers)
{
    char *str = my_snprintf("Hello %s, the answer is %d", "World", 42);
    cr_assert_str_eq(str, "Hello World, the answer is 42");
}

Test(my_snprintf, empty_string)
{
    char *str = my_snprintf("");
    cr_assert_str_eq(str, "");
}

Test(my_snprintf, null_string)
{
    char *str = my_snprintf(NULL);
    cr_assert_eq(str, NULL);
}

Test(my_snprintf, large_number)
{
    char *str = my_snprintf("%d", INT_MAX);
    char expected[12];
    sprintf(expected, "%d", INT_MAX);
    cr_assert_str_eq(str, expected);
}

Test(my_snprintf, hex_format)
{
    char *str = my_snprintf("%x", 255);
    cr_assert_str_eq(str, "ff");
}

Test(my_snprintf, octal_format)
{
    char *str = my_snprintf("%o", 8);
    cr_assert_str_eq(str, "10");
}

Test(my_snprintf, pointer_format)
{
    int x = 42;
    char *str = my_snprintf("%p", (void *)&x);
    char expected[20];
    sprintf(expected, "%p", (void *)&x);
    cr_assert_str_eq(str, expected);
}

Test(my_snprintf, percent_sign)
{
    char *str = my_snprintf("%%");
    cr_assert_str_eq(str, "%");
}

Test(my_snprintf, long_format)
{
    char *str = my_snprintf("%ld", LONG_MAX);
    char expected[21];
    sprintf(expected, "%ld", LONG_MAX);
    cr_assert_str_eq(str, expected);
}

Test(my_snprintf, unsigned_format)
{
    char *str = my_snprintf("%u", UINT_MAX);
    char expected[11];
    sprintf(expected, "%u", UINT_MAX);
    cr_assert_str_eq(str, expected);
}

Test(my_snprintf, integer_format_with_zero_padding)
{
    char *str = my_snprintf("%010d", 123);
    cr_assert_str_eq(str, "0000000123");
}

Test(my_snprintf, integer_format_with_left_justification)
{
    char *str = my_snprintf("%-10d", 123);
    cr_assert_str_eq(str, "123       ");
}

Test(my_snprintf, integer_format_with_sign)
{
    char *str = my_snprintf("%+d", 123);
    cr_assert_str_eq(str, "+123");
}

Test(my_snprintf, float_format_with_precision)
{
    char *str = my_snprintf("%.6f", 123.456789);
    cr_assert_str_eq(str, "123.456789");
}

Test(my_snprintf, float_format_with_width_and_precision)
{
    char *str = my_snprintf("%10.2f", 123.456);
    cr_assert_str_eq(str, "    123.46");
}

Test(my_snprintf, integer_format_with_width_and_zero_padding)
{
    char *str = my_snprintf("%010d", 123);
    cr_assert_str_eq(str, "0000000123");
}

Test(my_snprintf, integer_format_with_width_and_left_justification)
{
    char *str = my_snprintf("%-10d", 123);
    cr_assert_str_eq(str, "123       ");
}

Test(my_snprintf, integer_format_with_width_and_positive_sign)
{
    char *str = my_snprintf("%+10d", 123);
    cr_assert_str_eq(str, "      +123");
}

Test(my_snprintf, integer_format_with_hash_flag)
{
    char *str = my_snprintf("%#x", 123);
    cr_assert_str_eq(str, "0x7b");
}

Test(my_snprintf, float_format_with_hash_flag)
{
    char *str = my_snprintf("%#.0f", 123.0);
    cr_assert_str_eq(str, "123.");
}
