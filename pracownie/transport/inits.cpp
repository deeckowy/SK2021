#include "inits.hpp"

int socket_init()
{
    int sckt_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sckt_fd<0)
        panic("Socket error: ",true);
    else 
        return sckt_fd;
}

void connection_init(struct sockaddr_in *serv_addr,const int& port,
    const std::string& ip,const int& sock_fd)
{
    bzero(serv_addr,sizeof(*serv_addr));
    serv_addr->sin_family=AF_INET;
    serv_addr->sin_port=htons(port);
    int intptnerr=inet_pton(AF_INET,ip.c_str(),
        &serv_addr->sin_addr);
    if(intptnerr<0)
        panic("inet_pton error: ",true);
    int cnn=connect(sock_fd,(struct sockaddr*)serv_addr,sizeof(*serv_addr));
    if(cnn<0)
        panic("connection error: ",true);
}

int file_init(const char *file_name)
{
    int out_fd=open(file_name,O_CREAT|O_WRONLY,0600);
    if(out_fd<0)
        panic("File error: ",true);
    return out_fd;
}