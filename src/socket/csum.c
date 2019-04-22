/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** csum
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket/socket.h"

unsigned short csum(unsigned short *ptr,int nbytes)
{
    long sum;
    unsigned short oddbyte;
    short answer;

    sum=0;
    while (nbytes>1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }
    sum = (sum>>16) + (sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
    return(answer);
}