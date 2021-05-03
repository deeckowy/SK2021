#include "utils.hpp"

[[noreturn]] void panic(const std::string& msg,bool use_errno)
{
	std::cout<<msg<<(use_errno?std::strerror(errno):"")<<std::endl;
	exit(EXIT_FAILURE);
}

int validate_addr(const std::string& ip_addr)
{
	//regex from https://www.geeksforgeeks.org/how-to-validate-an-ip-address-using-regex/
	//mainly for this i've choosen c++ instead of c 
    auto rgx=std::regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    return std::regex_match(ip_addr,rgx);
}

int send_pckt(std::string &msg,struct sockaddr_in *server)
{
	return sendto();
}