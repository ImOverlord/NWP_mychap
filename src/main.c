/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "arguments/arguments.h"
#include "network/network.h"

static int validate_hostname(arguments_t **args)
{
    char ip[16];

    for (size_t args_index = 0; args[args_index] != NULL; args_index++) {
        if (strcmp(args[args_index]->name, "target") == 0) {
            if (hostname_to_ip(args[args_index]->value, ip)) {
                printf("No such hostname: '%s'\n", args[args_index]->value);
                return 0;
            }
            args[args_index]->value = ip;
            break;
        }
    }
    return 1;
}

int main(int ac, char *argv[])
{
    arguments_t **args = parse_args(ac, argv);

    if (!args)
        return ERROR;
    if (!valid_arguments(args))
        return ERROR;
    if (!validate_hostname(args))
        return ERROR;
    return SUCCESS;
}