#ifndef _TRACEROUTE_HPP_
#define _TRACEROUTE_HPP_
#include <cstdio>
#include <sys/time.h>
#include "inits.hpp"
#include "utils.hpp"

void traceroute(int sockfd,std::string &ip);

#endif