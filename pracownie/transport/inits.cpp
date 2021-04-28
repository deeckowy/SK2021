#include "inits.hpp"

int socket_init()
{
    int sckt_fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_ICMP);
    if(sckt_fd<0)
        panic("Socket error: ",true);
    else 
        return sckt_fd; 
}

int connection_init(int sck_fd)
{
    struct sockaddr_in
}

