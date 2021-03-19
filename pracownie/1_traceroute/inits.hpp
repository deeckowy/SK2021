#ifndef _INITS_HPP_
#define _INITS_HPP_

#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include "utils.hpp"

int sckt_init();
void packet_init(struct icmp *head,int seq);
void recipient_init(struct sockaddr_in *rec,std::string &ip);


#endif