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

static void create_socket_addresse_in(struct sockaddr_in *name, size_t port)
{
    name->sin_family        = AF_INET;
    name->sin_port          = htons(port);
    name->sin_addr.s_addr   = inet_addr("127.0.0.1");
}

static int bind_socket(raw_socket_t *raw_socket)
{
    struct sockaddr_in client;

    create_socket_addresse_in(&client, PORT);
    raw_socket->client = client;
    raw_socket->port = PORT;
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