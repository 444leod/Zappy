/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sample
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void init(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(example_suite, success_example, .init=init) {
    cr_assert_eq(0, 0);
}

Test(example_suite, failure_example, .init=init) {
    cr_assert_eq(0, 1);
}
