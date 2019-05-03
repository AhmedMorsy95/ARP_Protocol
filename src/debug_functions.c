#include "../headers/debug_functions.h"
#include "../headers/ethernet.h"
#include "../headers/includes.h"
#include "../headers/arp.h"
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_ethernet_packet(){
    printf("destination MAC : ");
    print_mac_address(ethernet_packet->dmac);
    printf("source MAC : ");
    print_mac_address(ethernet_packet->smac);
    printf("%4x\n",ethernet_packet->ethertype);
    if(ethernet_packet->ethertype == ETH_P_IP){
      printf("the packet is an IPv4 packet\n");
    }
    else if(ethernet_packet->ethertype == ETH_P_ARP){
      printf("the packet is an ARP packet\n");
    }
    else{
      printf("the packet type isnot supported\n");
    }
}

void print_mac_address(char *s){
  int i;
  for(i=0;i<6;i++){
      if(i) printf(":");
      printf("%.2hhx",s[i]);
   }
   printf("\n");
}

void print_ipv4_address(uint32_t ip){
      struct in_addr ip_addr;
      ip_addr.s_addr = ip;
      printf("The IP address is %s\n", inet_ntoa(ip_addr));
}
void print_arp_packet(){
    printf("source MAC : ");
    print_mac_address(arp_pckt->smac);
    printf("source ip : ");
    print_ipv4_address(arp_pckt->sip);
    printf("destination MAC : ");
    print_mac_address(arp_pckt->dmac);
    printf("destination ip : ");
    print_ipv4_address(arp_pckt->dip);
    printf("\n");	

}
