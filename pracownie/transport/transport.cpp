#include "transport.hpp"

typedef struct packet_info
{
    ssize_t size;
    char* buff;
}pckt_info;


void transport(struct sockaddr_in *server,ssize_t bytes,
                const int& out_fd,const int& sock_fd)
{
    ssize_t bytes_received=0;
    __uint128_t packet_mask=0;
    pckt_info data[WNDW_SIZE];
    memset(data,0,sizeof(pckt_info)*WNDW_SIZE);
    
    while(bytes_received!=bytes)
    {  
        ssize_t bytes_remain=bytes-bytes_received;
        int pckts_remain=bytes_remain/PCKT_SIZE;

        pckts_remain=pckts_remain>WNDW_SIZE?WNDW_SIZE:pckts_remain;
        
        if(pckts_remain!=0)
        {
            for(int i=0;i<pckts_remain;i++)
            {
                std::string msg=get_msg(bytes_received+i*PCKT_SIZE,PCKT_SIZE);
                send_pckt(msg,server,sock_fd);
            }
            if(pckts_remain!=WNDW_SIZE&&bytes_remain+pckts_remain*PCKT_SIZE!=bytes)
            {
                std::string msg=get_msg(bytes-bytes%PCKT_SIZE,bytes%PCKT_SIZE);
                send_pckt(msg,server,sock_fd);
            }
        }
        else
        {
            std::string msg=get_msg(bytes-bytes%PCKT_SIZE,bytes%PCKT_SIZE);
            send_pckt(msg,server,sock_fd);
        } 

        int pckt_ready=pckts_ready(sock_fd);

        //read packets
        for(int i=0;i<pckt_ready;i++)
        {
            ssize_t buffer_size=sizeof(char)*PCKT_SIZE+10;
            char *buffer=(char*)malloc(buffer_size);
            bool err_flag=false;
            auto pr=read_pckt(sock_fd,server,buffer,buffer_size);
            
            //invalid packet
            if(pr.first==0&&pr.second==0)err_flag=true;
        
            int idx=(pr.first-bytes_received)/PCKT_SIZE;
            //old packet
            if(idx<0)err_flag=true;

            //copy of already received packet 
            if(packet_mask&(1<<idx)||err_flag){free(buffer);continue;}

            packet_mask|=(1<<idx);
            data[idx].buff=buffer;
            data[idx].size=pr.second;
        }

        //save data to file 
        while(packet_mask&1)
        {
            ssize_t bytes_written=write(out_fd,data[0].buff,data[0].size);
            if(bytes_written<0)
                panic("write error: ",true);

            bytes_received+=bytes_written;
            free(data[0].buff);
            for(int i=0;i<WNDW_SIZE-1;i++)
                data[i]=data[i+1];
            data[WNDW_SIZE-1].buff=NULL;
            data[WNDW_SIZE-1].size=0;
            printf("%.2f %% completed\n",(float)bytes_received/(float)bytes*100.0);
            packet_mask>>=(ssize_t)1;
        }

    }
    for(int i=0;i<WNDW_SIZE;i++)
        if(data[i].buff)
            free(data[i].buff);
}