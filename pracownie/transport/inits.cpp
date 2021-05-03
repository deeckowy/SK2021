#include "inits.hpp"

int socket_init()
{
    int sckt_fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_ICMP);
    if(sckt_fd<0)
        panic("Socket error: ",true);
    else 
        return sckt_fd;
}

void connection_init(struct sockaddr_in *serv_addr,const int& port,
    const std::string& ip)
{
    memset(serv_addr,0,sizeof(*serv_addr));
    serv_addr->sin_addr=AF_INET;
    serv_addr->sin_port=htons(port);
    int intptnerr=inet_pton(AF_INET,ip.c_str(),
        &serv_addr->sin_addr.s_addr);
    if(intptnerr<0)
        panic("inet_pton error: ",true);
}

int file_init(const char *file_name)
{
    int out_fd=open(file_name,O_CREAT|O_APPEND|O_WRONLY);
    if(out_fd<0)
        panic("File error: ",true);
    return out_fd;
}