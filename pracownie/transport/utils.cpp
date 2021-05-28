#include "utils.hpp"

[[noreturn]] void panic(const std::string& msg,bool use_errno)
{
	std::cout<<msg<<(use_errno?std::strerror(errno):"")<<std::endl;
	exit(EXIT_FAILURE);
}

int validate_addr(const std::string& ip_addr)
{
    auto rgx=std::regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    return std::regex_match(ip_addr,rgx);
}

std::string get_msg(ssize_t offset,ssize_t size)
{
	std::string msg="GET "+std::to_string(offset)+" "+std::to_string(size)+"\n";
	return msg;
}

int pckts_ready(const int& sock_fd)
{
	struct timeval t;
	t.tv_usec=500;
	t.tv_sec=0;
	fd_set descriptors;
	FD_ZERO(&descriptors);
	FD_SET(sock_fd,&descriptors);
	int ready=select(sock_fd+1,&descriptors,NULL,NULL,&t);
	if(ready<0)
		panic("Select from sock_fd error: ",true);
	else 
		return ready;
}

std::pair<ssize_t,ssize_t> read_pckt(const int& sock_fd,struct sockaddr_in *server,
									char *data,ssize_t data_size)
{
	char buffer[UINT16_MAX];
	struct sockaddr_in sender;
	uint32_t sender_len=sizeof(sender);
	ssize_t bytes=recvfrom(sock_fd,buffer,UINT16_MAX,0,
							(struct sockaddr*)&sender,&sender_len);
	if(bytes<0)
		panic("recvfrom error: ",true);
	

	if(server->sin_addr.s_addr!=sender.sin_addr.s_addr||server->sin_port!=sender.sin_port)
		return {0,0};
	

	int i=0;
	ssize_t fs[2]={0,0};
	int flag=0;
	while(buffer[i]!='\n')
	{
		if(isdigit(buffer[i]))
		{
			while(isdigit(buffer[i]))
			{
				fs[flag]*=10;
				fs[flag]+=buffer[i]-'0';
				i++;
			}
			flag++;
		}
		else i++;
	}
	i++;
	memcpy(data,buffer+i,data_size);
	return {fs[0],fs[1]};
}


void send_pckt(std::string &msg,struct sockaddr_in *server,const int& sock_fd)
{
	ssize_t bytes_send=sendto(sock_fd,msg.c_str(),strlen(msg.c_str()),MSG_CONFIRM,
					(struct sockaddr*)server,sizeof(*server));

	if(bytes_send!=(ssize_t)msg.size())
		panic("sendto error: ",true);
}