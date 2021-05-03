#include <iostream>
#include "utils.hpp"
#include "inits.hpp"

int main(int argc,char **argv)
{
    if(argc!=4)
        panic("Usage: "+argv[0]+" <IPv4 addr> <port> <file_name> <size of data>");
    
    //checking correctness of user's data and creating 
    //most important variables 
    std::string ip_addr(argv[1]);
    if(!validate_addr(ip_addr))
        panic("Invalid ip addr! ",false);
    
    int port=atoi(argv[2]);
    if(port==0)
        panic("Invalid port number !",false);
    
    size_t data_size=atol(argv[4]);
    if(data_size==0)
        panic("Invalid data size !",false);

    //initializing descriptors and data structures
    int out_fd=file_init(argv[3]);

    int sckt_fd=socket_init();

    struct sockaddr_in srvr;

    connection_init(&srvr,port,ip_addr);


    return 0;
}