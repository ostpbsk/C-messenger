#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../inc/server.h"

int main(int argc, char *argv[]){
    struct addrinfo hints, *res, *p;
    int status;
    char ip_str[INET6_ADDRSTRLEN]; // Buffer for the IP string

    if (argc != 2)
    {
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; //IPv4 or IPv6 AF
    hints.ai_socktype = SOCK_STREAM; //TCP straming sockets

    if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) //argv[1] is the host name provided on the execution, NULL port is for any port
    {
        fprintf(stderr, "Cound not get address info for %s, GAI error: %s", argv[1], gai_strerror(status));
        return 2;
    }

    printf("Ip addresses for %s:\n.\n.\n", argv[1]);

    for (p = res; p != NULL; p = p->ai_next) { //
        void *addr; //address info addres in host-byte order
        char *ipver; // For IP version
        struct sockaddr_in *ipv4; //ipv4 handle
        struct sockaddr_in6 *ipv6; //ipv6 handle
        if (p->ai_family == AF_INET) { //if IPv4
            ipv4 = (struct sockaddr_in *) p->ai_addr; 
            addr = &(ipv4->sin_addr); //pointer to the address in network
            ipver = "IPv4";
        }
        else {
            ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr); 
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ip_str, sizeof ip_str); //Network to Printable conversion, saves in ip_str
        printf("%s: %s\n", ipver, ip_str);
    }


    //Free the used Linked list
    freeaddrinfo(res);
    return 0;
}