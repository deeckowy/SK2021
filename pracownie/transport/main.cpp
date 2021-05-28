#include <iostream>
#include "utils.hpp"
#include "inits.hpp"
#include "transport.hpp"

int main(int argc,char **argv)
{
    if(argc!=5)
        panic("Usage: "+std::string(argv[0])+" <IPv4 addr> <port> <file_name> <size of data>",false);
    
    std::string ip_addr(argv[1]);
    if(!validate_addr(ip_addr))
        panic("Invalid ip addr! ",false);
    
    int port=atoi(argv[2]);
    if(port==0)
        panic("Invalid port number !",false);
    
    size_t data_size=atol(argv[4]);
    if(data_size==0)
        panic("Invalid data size !",false);

    int out_fd=file_init(argv[3]);

    int sckt_fd=socket_init();

    struct sockaddr_in srvr;

    connection_init(&srvr,port,ip_addr,sckt_fd);

    transport(&srvr,data_size,out_fd,sckt_fd);
    
    close(sckt_fd);
    close(out_fd);

    return 0;
}