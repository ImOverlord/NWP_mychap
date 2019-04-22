/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** socket
*/

#ifndef SOCKET_MY_H_
#define SOCKET_MY_H_

#include <netinet/udp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct raw_socket_s {
    int sock;
    int port;
    struct sockaddr_in client;
} raw_socket_t;

struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t udp_length;
};

raw_socket_t *crate_raw_socket();
char *send_socket(char *target, int port, raw_socket_t *sock, char *message);
unsigned short csum(unsigned short *ptr,int nbytes);
void fill_pseudo_header(
    struct udphdr *udph,
    char *data,
    struct sockaddr_in sin
);
void fill_udp_header(struct udphdr *udph, char *data, int s_port, int d_port);
int fill_ip_header(
    struct iphdr *iph,
    char *datagram,
    char *data,
    struct sockaddr_in sin
);
void fill_server_info(struct sockaddr_in *sin, char *target, int port);
#endif /* !SOCKET_H_ */
