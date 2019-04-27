/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** fill_header
*/

#include <malloc.h>
#include <string.h>
#include "socket/socket.h"

void fill_server_info(struct sockaddr_in *sin, char *target, int port)
{
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(target);
}

int fill_ip_header(
    struct iphdr *iph,
    char *data,
    raw_socket_t *sock
)
{
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len =
    sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
    iph->id = htonl (54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = sock->client.sin_addr.s_addr;
    iph->daddr = sock->server.sin_addr.s_addr;
    iph->check = 0;
    return 0;
}

void fill_udp_header(struct udphdr *udph, char *data, int s_port, int d_port)
{
    udph->source = htons (s_port);
    udph->dest = htons (d_port);
    udph->len = htons(8 + strlen(data));
    udph->check = 0;
}