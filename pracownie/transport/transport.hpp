#ifndef _TRANSPORT_HPP_
#define _TRANSPORT_HPP_

#include <iostream>
#include "utils.hpp"

void transport(struct sockaddr_in *server,size_t bytes,const int& out_fd);


#endif