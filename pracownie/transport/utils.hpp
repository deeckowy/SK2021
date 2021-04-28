#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <iostream>
#include <regex>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>

[[noreturn]]void panic(std::string msg,bool use_errno);
int validate_addr(std::string ip_addr);


#endif