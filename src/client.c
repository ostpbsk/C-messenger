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


int main() {
    int status;
    struct addrinfo hints; //Look up struct for the socket info
    struct addrinfo *servinfo; // Pointer to the results of the getaddrinfo() function

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // Either IPv4 or IPv6 address family
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    /***
     * 
     * @brief: DNS ans Service lookup utilizing hints struct
     * 
     * @details: This fucntion fills a linked-list of structures addrinfo
     * using the criterias referenced in hints struct. This is a server-side part
     * of the program, so passing NULL means "bind to any local host name"
     *    
     * @param __name: Host's DNS name or IP as a string (NULL for localhost)
     * @param __port: Servie name or a Port number as a string 
     * @param __req: Pointer to the addrinfo struct containing criteria
     * @param __pai: Output pointer to the strucutr that will be referencing a linked list
     * 
     * @return: 0 on success, not 0 on error
     */
    if((status = getaddrinfo("localhost", PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "Error: Could not get address info. GAI error: %d\n", gai_strerror);
        exit(1);
    }






    // Free the linked list when done
    freeaddrinfo(servinfo);
    return 0;
}
