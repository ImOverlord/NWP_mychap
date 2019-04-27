/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** create_raw_socket
*/

#include <malloc.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket/socket.h"

static int bind_socket(raw_socket_t *raw_socket)
{
    struct sockaddr_in client;
    socklen_t name_size = sizeof(client);

    if (getsockname(raw_socket->sock,
    (struct sockaddr *) &client, &name_size) < 0)
        return 0;
    raw_socket->client = client;
    raw_socket->port = 3000;
    return 1;
}

raw_socket_t *crate_raw_socket()
{
    raw_socket_t *raw_socket;
    int one = 1;
    const int *val = &one;
    int s = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);

    if (s == -1)
        return NULL;
    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
        return NULL;
    raw_socket = malloc(sizeof(raw_socket_t));
    if (!raw_socket)
        return NULL;
    raw_socket->sock = s;
    if (!bind_socket(raw_socket))
        return NULL;
    return raw_socket;
}