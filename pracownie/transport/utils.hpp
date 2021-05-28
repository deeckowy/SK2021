#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <regex>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <utility>
#include <netinet/ip.h>

[[noreturn]]void panic(const std::string& msg,bool use_errno);

int validate_addr(const std::string& ip_addr);

std::string get_msg(ssize_t offset,ssize_t size);

int pckts_ready(const int& sock_fd);

std::pair<ssize_t,ssize_t> read_pckt(const int& sock_fd,struct sockaddr_in *server,
                                    char *data,ssize_t data_size);

void send_pckt(std::string &msg,struct sockaddr_in *server,const int& sock_fd);

#endif