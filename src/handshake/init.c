/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** init
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handshake/handshake.h"
#include "socket/socket.h"

static char *get_by_key(arguments_t **args, char *key)
{
    for (size_t args_index = 0; args[args_index] != NULL; args_index++)
        if (strcmp(args[args_index]->name, key) == 0)
            return args[args_index]->value;
    return NULL;
}

static int error_handling(char *response)
{
    if (!response) {
        printf("KO\n");
        return 1;
    }
    if (strcmp(response, ERROR_MSG) == 0) {
        printf("KO\n");
        return 1;
    }
    if (strcmp(response, KO_MSG) == 0) {
        printf("KO\n");
        return 1;
    }
    return 0;
}

int init_handshake(arguments_t **args)
{
    char *target = get_by_key(args, "target");
    int port = atoi(get_by_key(args, "port"));
    char *password = get_by_key(args, "password");
    char *response;
    char *key;

    raw_socket_t *sock = crate_raw_socket();
    if (!sock)
        return 0;
    fill_server_info(&sock->server, target, port);
    response = send_socket(target, port, sock, PHASE1_MESG);
    if (error_handling(response))
        return 0;
    key = calloc(NONCE_LENGTH + strlen(password), sizeof(char));
    strcpy(key, response);
    strcat(key, password);
    response = send_socket(target, port, sock, sha256(key));
    if (error_handling(response))
        return 0;
    printf("Secret: '%s'\n", response);
    return 1;
}