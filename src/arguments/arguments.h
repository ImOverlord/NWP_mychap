/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#define SUCCESS     0
#define ERROR       84

typedef struct internal_arguments_s {
    char *name;
    char *long_option;
    char *short_option;
    char *value;
} internal_arguments_t;

typedef struct arguments_s {
    char *name;
    char *value;
} arguments_t;

arguments_t **parse_args(int ac, char *argv[]);
int valid_arguments(arguments_t **args);

#endif /* !ARGUMENTS_H_ */
