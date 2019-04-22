/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** send_socket
*/

#include<stdio.h>	//for printf
#include<string.h> //memset
#include<sys/socket.h>	//for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include <netinet/in.h>
#include <sys/socket.h>
#include "socket/socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *clean_reponse(char *buffer)
{
    char *clean = calloc(
        (buffer + sizeof(struct iphdr) + sizeof(struct udphdr)),
        sizeof(char)
    );
    clean = strdup(buffer + sizeof(struct iphdr) + sizeof(struct udphdr));
    free(buffer);
    return clean;
}

char *get_reponse(raw_socket_t *sock)
{
    char *buffer;
    int size;

    for (int i = 0; i < 2; i++) {
        buffer = calloc(1024, sizeof(char));
        size = recv(sock->sock, buffer, 1024, 0);
        buffer[size] = '\0';
        if (i == 1)
            return clean_reponse(buffer);
        free(buffer);
    }
    return NULL;
}

char *send_socket(
    char *target,
    int port,
    raw_socket_t *sock,
    char *message
)
{
    char datagram[4096] , *data;
    struct iphdr *iph = (struct iphdr *) datagram;
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
    struct sockaddr_in sin;

    fill_server_info(&sin, target, port);
    memset(datagram, 0, 4096);
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data, message);
    fill_ip_header(iph, datagram, data, sin);
    fill_udp_header(udph, data, sock->port, port);
    fill_pseudo_header(udph, data, sin);
    if (sendto (sock->sock, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
        return NULL;
    return get_reponse(sock);
}