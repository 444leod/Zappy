/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tablen
*/

#include "testing.h"
#include "lib.h"

Test(tablen, basic_string_tab)
{
    const char *tab[] = {"Hello", "World", "!", NULL};

    cr_assert_eq(tablen((const void **)tab), 3);
}

Test(tablen, empty_tab)
{
    const char *tab[] = {NULL};

    cr_assert_eq(tablen((const void **)tab), 0);
}

Test(tablen, null_tab)
{
    cr_assert_eq(tablen(NULL), 0);
}

Test(tablen, basic_int_tab)
{
    int a, b, c, d, e = 0;
    const int *tab[] = {&a, &b, &c, &d, &e, NULL};

    cr_assert_eq(tablen((const void **)tab), 5);
}

Test(tablen, empty_int_tab)
{
    const int *tab[] = {NULL};

    cr_assert_eq(tablen((const void **)tab), 0);
}

Test(tablen, basic_float_tab)
{
    float a, b, c, d, e = 0;
    const float *tab[] = {&a, &b, &c, &d, &e, NULL};

    cr_assert_eq(tablen((const void **)tab), 5);
}

Test(tablen, empty_float_tab)
{
    const float *tab[] = {NULL};

    cr_assert_eq(tablen((const void **)tab), 0);
}

Test(tablen, basic_double_tab)
{
    double a, b, c, d, e = 0;
    const double *tab[] = {&a, &b, &c, &d, &e, NULL};

    cr_assert_eq(tablen((const void **)tab), 5);
}

Test(tablen, empty_double_tab)
{
    const double *tab[] = {NULL};

    cr_assert_eq(tablen((const void **)tab), 0);
}

Test(tablen, basic_void_tab)
{
    int a, b, c, d, e = 0;
    const void *tab[] = {&a, &b, &c, &d, &e, NULL};

    cr_assert_eq(tablen(tab), 5);
}


