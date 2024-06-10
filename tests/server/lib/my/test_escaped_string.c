/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** escaped_string
*/

#include "testing.h"
#include "lib.h"

Test(escaped_string, get_basic_string)
{
    char *str = get_escaped_string("HelloWorld");
    cr_assert_str_eq(str, "HelloWorld");
    free(str);
}

Test(escaped_string, get_string_with_spaces)
{
    char *str = get_escaped_string("Hello World");
    cr_assert_str_eq(str, "Hello World");
    free(str);
}

Test(escaped_string, get_string_with_tabs)
{
    char *str = get_escaped_string("Hello\tWorld");
    cr_assert_str_eq(str, "Hello\\tWorld");
    free(str);
}

Test(escaped_string, get_string_with_newlines)
{
    char *str = get_escaped_string("Hello\nWorld");
    cr_assert_str_eq(str, "Hello\\nWorld");
    free(str);
}

Test(escaped_string, get_string_with_backslashes)
{
    char *str = get_escaped_string("Hello\\World");
    cr_assert_str_eq(str, "Hello\\\\World");
    free(str);
}

Test(escaped_string, get_string_with_quotes)
{
    char *str = get_escaped_string("Hello\"World");
    cr_assert_str_eq(str, "Hello\\\"World");
    free(str);
}

Test(escaped_string, get_string_with_single_quotes)
{
    char *str = get_escaped_string("Hello'World");
    cr_assert_str_eq(str, "Hello\\'World");
    free(str);
}

Test(escaped_string, get_string_with_backslash_v)
{
    char *str = get_escaped_string("Hello\vWorld");
    cr_assert_str_eq(str, "Hello\\vWorld");
    free(str);
}

Test(escaped_string, get_string_with_backslash_b)
{
    char *str = get_escaped_string("Hello\bWorld");
    cr_assert_str_eq(str, "Hello\\bWorld");
    free(str);
}

Test(escaped_string, get_string_with_backslash_r)
{
    char *str = get_escaped_string("Hello\rWorld");
    cr_assert_str_eq(str, "Hello\\rWorld");
    free(str);
}

Test(escaped_string, get_string_with_backslash_f)
{
    char *str = get_escaped_string("Hello\fWorld");
    cr_assert_str_eq(str, "Hello\\fWorld");
    free(str);
}

Test(escaped_string, get_string_with_backslash_a)
{
    char *str = get_escaped_string("Hello\aWorld");
    cr_assert_str_eq(str, "Hello\\aWorld");
    free(str);
}

Test(escaped_string, get_string_with_question_mark)
{
    char *str = get_escaped_string("Hello?World");
    cr_assert_str_eq(str, "Hello\\?World");
    free(str);
}

Test(escaped_string, get_string_with_special_chars)
{
    char *str = get_escaped_string("Hello\n\tWorld");
    cr_assert_str_eq(str, "Hello\\n\\tWorld");
    free(str);
}

Test(escaped_string, get_string_with_multiple_special_chars)
{
    char *str = get_escaped_string("Hello\n\tWorld\n");
    cr_assert_str_eq(str, "Hello\\n\\tWorld\\n");
    free(str);
}

Test(escaped_string, get_string_with_empty_string)
{
    char *str = get_escaped_string("");
    cr_assert_str_eq(str, "");
    free(str);
}

Test(escaped_string, display_escaped_string_basic)
{
    cr_redirect_stdout();
    print_escaped("HelloWorld");
    fflush(stdout);
    cr_assert_stdout_eq_str("HelloWorld\n");
}

Test(escaped_string, display_escaped_string_spaces)
{
    cr_redirect_stdout();
    print_escaped("Hello World");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello World\n");
}

Test(escaped_string, display_escaped_string_basic1)
{
    cr_redirect_stdout();
    print_escaped("Hello\nWorld");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\nWorld\n");
}

Test(escaped_string, display_escaped_string_basic2)
{
    cr_redirect_stdout();
    print_escaped("Hello\tWorld");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\tWorld\n");
}

Test(escaped_string, display_escaped_string_basic3)
{
    cr_redirect_stdout();
    print_escaped("Hello\\World");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\\\World\n");
}

Test(escaped_string, display_escaped_string_advanced1)
{
    cr_redirect_stdout();
    print_escaped("Hello\n\tWorld");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\n\\tWorld\n");
}

Test(escaped_string, display_escaped_string_advanced2)
{
    cr_redirect_stdout();
    print_escaped("Hello\n\tWorld\n");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\n\\tWorld\\n\n");
}

Test(escaped_string, display_escaped_string_advanced3)
{
    cr_redirect_stdout();
    print_escaped("Hello\n\tWorld\n\n");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\\n\\tWorld\\n\\n\n");
}
