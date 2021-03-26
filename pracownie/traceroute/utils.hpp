#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <cassert>
#include <regex>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


[[noreturn]]void panic(std::string msg,bool ern);
u_int16_t compute_icmp_checksum (const void *buff, int length);
int compute_seq(int ttl,int i);
bool is_last(int seq,int ttl);
int validate_addr(std::string ip_addr);
void send_pckt(struct icmp *pckt,struct sockaddr_in *rec,int sockfd);
int is_ready(int sockfd,struct timeval *t);
std::string *read_packets(int sockfd,int ttl,bool *dest_reached);
void print_ips(std::string *ips,int i);
void print_avg_time(struct timeval *times);

#endif