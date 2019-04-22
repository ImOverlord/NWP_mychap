/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** resolve_hostname
*/

#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "network/network.h"

int hostname_to_ip(char *hostname, char *ip)
{
    struct hostent *host;
    struct in_addr **addr_list;

    host = gethostbyname(hostname);
    if (host == NULL)
        return 1;
    addr_list = (struct in_addr **)host->h_addr_list;
    if (addr_list[0] != NULL) {
        strcpy(ip, inet_ntoa(*addr_list[0]));
        return 0;
    }
    return 1;
}
