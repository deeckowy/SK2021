#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <regex>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>

[[noreturn]]void panic(const std::string& msg,bool use_errno);
int validate_addr(const std::string& ip_addr);
int send_pckt(std::string &msg,struct sockaddr_in *server);

#endif