#include "inits.hpp"

int sckt_init()
{
    int sckt_fd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    if(sckt_fd<0)
    {
        printf("Socket error: %s\n",std::strerror(errno));
        return -1;
    }
    else 
        return sckt_fd; 
}

int packet_init(struct icmp *head,int seq)
{
    head->icmp_type=ICMP_ECHO;
    head->icmp_code=0;
    head->icmp_hun.ih_idseq.icd_id=getpid();
    head->icmp_hun.ih_idseq.icd_seq=seq;
    head->icmp_cksum=0;
    head->icmp_cksum=compute_icmp_checksum(
        (u_int16_t*)&header, sizeof(header));
}
