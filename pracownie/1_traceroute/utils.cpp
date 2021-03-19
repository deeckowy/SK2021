#include "utils.hpp"

//this noreturn look is weird
[[noreturn]] void panic(std::string msg,bool ern)
{
	std::cout<<msg<<(ern?std::strerror(errno):"")<<std::endl;
	exit(EXIT_FAILURE);
}


u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = (uint16_t*)buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

int compute_seq(int ttl,int i)
{
    return ttl<<2|i;
}

bool is_current(int seq,int ttl)
{
    return seq>>2==ttl;
}

int validate_addr(std::string ip_addr)
{
	//i've stolen regex from https://www.geeksforgeeks.org/how-to-validate-an-ip-address-using-regex/
	//it's only for IPv4 but i think that's we don't have to worry about IPv6
	//mainly for this i've choosen c++ instead of c 
    auto rgx=std::regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    return std::regex_match(ip_addr,rgx);
}

void send_pckt(struct icmp *pckt,struct sockaddr_in *rec,int sockfd)
{
	ssize_t head_size=sizeof(*pckt);
	ssize_t bytes_send=sendto(sockfd,pckt,head_size,0,(struct sockaddr*)rec,sizeof(*rec));
	if(bytes_send<0)
		panic("Packet sending error: ",true);
	if(bytes_send!=head_size)
		panic("Packet wasn't fully send!",false);
}

int is_ready(int sockfd,struct timeval *t)
{
	fd_set descriptors;
	FD_ZERO(&descriptors);
	FD_SET(sockfd,&descriptors);
	int ready=select(sockfd+1,&descriptors,NULL,NULL,t);
	if(ready<0)
		panic("Select from sockfd error: ",true);
	else 
		return ready;
}

bool check_act_texcd(void *ichdr,int ttl)
{
	struct ip *ip_header=(struct ip*)((uint8_t*)ichdr+sizeof(struct icmp));
	ssize_t ip_header_size  = 4 * ip_header->ip_hl;
	struct icmp* icmp_header = (struct icmp*)((uint8_t*)ichdr+ip_header_size);
	return getpid()==icmp_header->icmp_hun.ih_idseq.icd_id&&
		is_current(icmp_header->icmp_hun.ih_idseq.icd_seq,ttl);
}


std::string *read_packets(int sockfd,int ttl,bool *dest_reached)
{
	struct sockaddr_in sender;
	socklen_t sender_len = sizeof(sender);
	u_int8_t buffer[IP_MAXPACKET];
	ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0,               
		(struct sockaddr*)&sender, &sender_len);
	if(packet_len<0)
		panic("Packet reading error: ",true);
	char ip_str[20];    
 
	inet_ntop (AF_INET, &(sender.sin_addr), ip_str, sizeof(ip_str));
	struct ip* ip_header = (struct ip*)buffer;
	ssize_t ip_header_size  = 4 * ip_header->ip_hl;
	struct icmp* icmp_header = (struct icmp*)(buffer+ip_header_size);
	auto *str=new std::string(ip_str);

	// this looks very bad but it works !
	// mainly our icmp from response when it gets TLL_EXCEEDED is build 
	// like this new_icmp->orginal_ip->orginal_icmp <- we have to get here to 
	// get our id and seq
	if(icmp_header->icmp_type==ICMP_TIME_EXCEEDED)
		icmp_header=(struct icmp*)((uint8_t*)&icmp_header->icmp_dun.id_ip.idi_ip+sizeof(struct ip));

	if(getpid()!=icmp_header->icmp_hun.ih_idseq.icd_id||
		!is_current(icmp_header->icmp_hun.ih_idseq.icd_seq,ttl))
		return NULL;

	if(icmp_header->icmp_type==ICMP_ECHOREPLY)
		*dest_reached=true;
	return str;
}

void print_ips(std::string *ips,int i)
{
	int x=0;
	while(x!=i)
	{
		std::cout<<ips[x]<<" ";
		x++;
	}
}

void print_avg_time(struct timeval *times)
{
	uint64_t usecs=0;
	for(int i=0;i<3;i++)
		usecs+=times[i].tv_usec;
	std::cout<<usecs/1000/3<<"ms"<<std::endl;
}