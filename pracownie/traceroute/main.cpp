#include "utils.hpp"
#include "inits.hpp"
#include "traceroute.hpp"

int main(int argc,char **argv)
{
    if(argc!=2)
        panic("Usage "+std::string(argv[0])+" <IPv4 address>",false);
    std::string ip(argv[1]);
    if(!validate_addr(ip))
        panic("Wrong IPv4 address correct syntax is [0-255].[0-255].[0-255].[0-255]",false);
    int sckfd=sckt_init();
    traceroute(sckfd,ip);
    return 0;
}