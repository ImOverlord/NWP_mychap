/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** send_socket
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket/socket.h"

static char *clean_reponse(char *buffer)
{
    char *clean = calloc(
        (buffer + sizeof(struct iphdr) + sizeof(struct udphdr)),
        sizeof(char)
    );
    clean = strdup(buffer + sizeof(struct iphdr) + sizeof(struct udphdr));
    free(buffer);
    return clean;
}

static int is_resp_packet(char *buffer, raw_socket_t *sock)
{
    int packet_port =
    ntohs(((struct udphdr *)(buffer + sizeof(struct iphdr)))->dest);
    if (packet_port == sock->port)
        return 1;
    return 0;
}

static char *get_response(raw_socket_t *sock)
{
    char *buffer;
    int size;

    for (int i = 0; i >= 0; i++) {
        buffer = calloc(1024, sizeof(char));
        size = recvfrom(sock->sock, buffer, 1024, 0,
        NULL, NULL);
        buffer[size] = '\0';
        if (is_resp_packet(buffer, sock))
            return clean_reponse(buffer);
        free(buffer);
    }
    return NULL;
}

char *send_socket(
    int port,
    raw_socket_t *sock,
    char *message
)
{
    char datagram[4096] , *data;
    struct iphdr *iph = (struct iphdr *) datagram;
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));

    memset(datagram, 0, 4096);
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data, message);
    fill_ip_header(iph, data, sock);
    fill_udp_header(udph, data, sock->port, port);
    if (sendto (sock->sock, datagram, iph->tot_len, 0,
    (struct sockaddr *) &sock->server, sizeof (sock->server)) < 0)
        return NULL;
    return get_response(sock);
}