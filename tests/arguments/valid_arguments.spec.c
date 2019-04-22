/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** valid_arguments.spec
*/

#include <criterion/criterion.h>
#include "arguments/arguments.h"

Test(valid_arguments, valid)
{
    int ac = 7;
    char *argv[7] = {
        "a.out",
        "--port",
        "3000",
        "--password",
        "hey",
        "--target",
        "hello"
    };
    arguments_t **args = parse_args(ac, argv);

    cr_expect_not_null(args);
    cr_expect_eq(valid_arguments(args), 1);
}

Test(valid_arguments, missin)
{
    int ac = 5;
    char *argv[5] = {
        "a.out",
        "--port",
        "3000",
        "--password",
        "hey",
    };
    arguments_t **args = parse_args(ac, argv);

    cr_expect_not_null(args);
    cr_expect_eq(valid_arguments(args), 0);
}