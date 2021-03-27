#include "traceroute.hpp"

void traceroute(int sockfd,std::string &ip)
{
    struct sockaddr_in recipient;
    recipient_init(&recipient,ip);
    bool dest_reached=false;
    for(int ttl=1;ttl<=30;ttl++)
    {
        int ttl_set=setsockopt(sockfd,IPPROTO_IP,IP_TTL,&ttl,sizeof(ttl));
        if(ttl_set<0)
            panic("Setting ttl error: ",true);
        struct timeval t;
        t.tv_sec=1;
        t.tv_usec=0;
        for(int i=1;i<=3;i++)
        {
            struct icmp pckt;
            packet_init(&pckt,compute_seq(ttl,i));
            send_pckt(&pckt,&recipient,sockfd);
        }
        std::string *ips=new std::string[3];
        struct timeval times[3];
        int read=0;
        while(is_ready(sockfd,&t))
        {
            std::string *out=read_packets(sockfd,ttl,&dest_reached);
            if(!out)
                continue;
            ips[read]=*out;
            times[read].tv_sec=1;
            times[read].tv_usec=0;
            timersub(times+read,&t,times+read);
            read++;
        }
        print_ips(ips,read);
        if(read==0)
            std::cout<<"*"<<std::endl;
        else if(read<3)
            std::cout<<"???"<<std::endl;
        else 
            print_avg_time(times);
        if(dest_reached)
            return;
    }
}