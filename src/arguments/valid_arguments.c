/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** valid_arguments
*/

#include <string.h>
#include "arguments/arguments.h"

int valid_arguments(arguments_t **args)
{
    for (size_t args_index = 0; args[args_index] != NULL; args_index++)
        if (args[args_index]->value == NULL)
            return 0;
    return 1;
}