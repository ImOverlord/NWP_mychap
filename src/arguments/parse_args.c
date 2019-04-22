/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** parse_args
*/

#include <string.h>
#include <malloc.h>
#include "arguments/arguments.h"

static int match_option(char *option, internal_arguments_t *options)
{
    for (size_t index = 0; options[index].long_option != 0; index++) {
        if (strcmp(option, options[index].long_option) == 0)
            return index;
        if (strcmp(option, options[index].short_option) == 0)
            return index;
    }
    return -1;
}

static size_t get_args_size(internal_arguments_t *args)
{
    size_t size;
    for (size = 0; args[size].name != 0; size++);
    return size;
}

static arguments_t **create_arguments(internal_arguments_t *args)
{
    size_t index;
    size_t size = get_args_size(args);
    arguments_t **options = malloc(sizeof(*options) * (size + 1));

    if (!options)
        return NULL;
    for (index = 0; index < size; index++) {
        options[index] = malloc(sizeof(arguments_t));
        if (!options[index])
            return NULL;
        options[index]->name = args[index].name;
        options[index]->value = args[index].value;
    }
    options[index] = NULL;
    return options;
}

arguments_t **parse_args(int ac, char *argv[])
{
    int found_index = -1;
    static internal_arguments_t options[] = {
        {"target", "--target", "-t", NULL},
        {"port", "--port", "-p", NULL},
        {"password", "--password", "-P", NULL},
        {0, 0, 0, 0}
    };

    if (ac % 2 == 0 || ac == 1)
        return NULL;
    for (int index = 1; index < ac; index++) {
        found_index = match_option(argv[index], options);
        if (found_index >= 0) {
            options[found_index].value = argv[index + 1];
            index++;
        }
    }
    return create_arguments(options);
}