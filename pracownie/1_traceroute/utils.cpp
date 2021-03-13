#include "utils.hpp"

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
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

bool is_last(int seq,int ttl)
{
    return seq>>2==ttl;
}

int validate_addr(char *ip_addr)
{
    auto=std::regex("\d{1-3}.\d{1-3}.\d{1-3}.\d{1-3}");
    return std::regex_match();
}