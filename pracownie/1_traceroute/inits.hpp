
#ifndef _INITS_HPP_
#define _INITS_HPP_

#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include "utils.hpp"

int sckt_init();
int packet_init(struct icmp *head,int seq);

#endif