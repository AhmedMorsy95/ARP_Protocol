#include "../headers/includes.h"
#include "../headers/ethernet.h"
#include "../headers/tap_tun.h"

struct ethernet_header *ethernet_packet;
int ethernet_len;

// fills ethernet_header parts
void parse_ethernet(){
     ethernet_packet = (struct ethernet_header *) tap_buffer;
     ethernet_packet->ethertype = ntohs(ethernet_packet->ethertype);
     //network to host short function converts the unsigned short integer netshort from network byte order to host byte order.
     handle_packet();
}

void handle_packet(){
  if(ethernet_packet->ethertype == ETH_P_IP){
      printf("The packet is an IPv4 packet, parsing it now\n\n");
  }
  else if(ethernet_packet->ethertype == ETH_P_ARP){
      printf("The packet is an ARP packet, parsing it now\n\n");
      parse_arp();
  }
  else{
    printf("the packet type isnot supported, skipping it!!\n\n");
  }
}
