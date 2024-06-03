/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sample
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void init(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/**
 * A boolean assertion example.
 * You can simply check equalities this way.
*/
Test(example_suite, assert_example_one) {
    cr_assert(0 == 1);
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
