#ifndef _TRANSPORT_HPP_
#define _TRANSPORT_HPP_

#include <iostream>
#include <unistd.h>
#include "utils.hpp"

#define PCKT_SIZE 1000
#define WNDW_SIZE 127

void transport(struct sockaddr_in *server,ssize_t bytes,const int& out_fd,const int& sock_fd);


#endif