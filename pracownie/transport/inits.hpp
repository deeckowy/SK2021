#ifndef _INITS_HPP_
#define _INITS_HPP_

#include <fcntl.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "utils.hpp"

int socket_init();
void connection_init(struct sockaddr_in *serv_addr,
    const int& port,const std::string& ip,const int& sock_fd);
int file_init(const char *file_name);

#endif