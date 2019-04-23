/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** parse_args
*/

#include <criterion/criterion.h>
#include "arguments/arguments.h"

Test(parse_args, simple)
{
    arguments_t **args;
    int ac = 3;
    char *argv[3] = {"a.out", "--target", "hello"};

    args = parse_args(ac, argv);
    cr_expect_str_eq(args[0]->value, "hello");
    cr_expect_str_eq(args[0]->name, "target");
}

Test(parse_args, error)
{
    arguments_t **args;
    int ac = 2;
    char *argv[2] = {"a.out", "--target"};

    args = parse_args(ac, argv);
    cr_expect_null(args);
}

Test(parse_args, no_args)
{
    arguments_t **args;
    int ac = 2;
    char *argv[2] = {"a.out", "--target"};

    args = parse_args(ac, argv);
    cr_expect_null(args);
}

Test(parse_args, should_detect_long_options)
{
    arguments_t **args;
    int ac = 3;
    char *argv[3] = {"a.out", "--target", "hello"};

    args = parse_args(ac, argv);
    cr_expect_str_eq(args[0]->value, "hello");
    cr_expect_str_eq(args[0]->name, "target");
}

Test(parse_args, should_detect_short_options)
{
    arguments_t **args;
    int ac = 3;
    char *argv[3] = {"a.out", "-t", "hello"};

    args = parse_args(ac, argv);
    cr_expect_str_eq(args[0]->value, "hello");
    cr_expect_str_eq(args[0]->name, "target");
}

Test(parse_args, should_skip_invalid_options)
{
    arguments_t **args;
    int ac = 5;
    char *argv[5] = {"a.out", "-a", "hello", "-t", "hey"};

    args = parse_args(ac, argv);
    cr_expect_str_eq(args[0]->value, "hey");
    cr_expect_str_eq(args[0]->name, "target");
}