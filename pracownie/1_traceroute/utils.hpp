#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <cassert>
#include <regex>

u_int16_t compute_icmp_checksum (const void *buff, int length);
int compute_seq(int ttl);
bool is_last(int seq,int ttl);
int validate_addr(char *ip_addr);
#endif