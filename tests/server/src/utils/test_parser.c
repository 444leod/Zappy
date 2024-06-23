/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_parser
*/

#include "testing.h"
#include "zappy.h"

Test(parser_suite, null_command, .timeout=3)
{
    char **args = parse_command_args(NULL);

    cr_assert_null(args);
}

Test(parser_suite, empty_command, .timeout=3)
{
    char *cmd = "";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 0);
}

Test(parser_suite, no_args, .timeout=3)
{
    char *cmd = "command";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 1);
    cr_assert_str_eq(args[0], "command");
    cr_assert_null(args[1]);
}

Test(parser_suite, one_arg, .timeout=3)
{
    char *cmd = "command arg";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 2);
    cr_assert_str_eq(args[0], "command");
    cr_assert_str_eq(args[1], "arg");
    cr_assert_null(args[2]);
}

Test(parser_suite, no_args_with_quotes, .timeout=3)
{
    char *cmd = "\"simple_quotes\"";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 1);
    cr_assert_str_eq(args[0], "simple_quotes");
    cr_assert_null(args[1]);
}

Test(parser_suite, one_arg_with_quotes, .timeout=3)
{
    char *cmd = "\"one_arg\" \"with_quotes\"";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 2);
    cr_assert_str_eq(args[0], "one_arg");
    cr_assert_str_eq(args[1], "with_quotes");
    cr_assert_null(args[2]);
}

Test(parser_suite, quotes_no_padding, .timeout=3)
{
    char *cmd = "\"quotes\"\"no_padding\"";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 2);
    cr_assert_str_eq(args[0], "quotes");
    cr_assert_str_eq(args[1], "no_padding");
    cr_assert_null(args[2]);
}

Test(parser_suite, one_quote_no_padding, .timeout=3)
{
    char *cmd = "\"one_quote\"no_padding";
    char **args = parse_command_args(cmd);
    int len = tablen((const void **)args);

    cr_assert_not_null(args);
    cr_assert_eq(len, 2);
    cr_assert_str_eq(args[0], "one_quote");
    cr_assert_str_eq(args[1], "no_padding");
    cr_assert_null(args[2]);
}

Test(parser_suite, unmatched_quote, .timeout=3)
{
    char *cmd = "\"hello world";
    char **args = parse_command_args(cmd);

    cr_assert_null(args);
}
