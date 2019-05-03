#include "../headers/arp.h"
#include "../headers/ethernet.h"

struct arp_packet *arp_pckt;

void parse_arp(){
    arp_pckt = (struct arp_packet *) ethernet_packet->payload;
    arp_pckt->hardware_type = ntohs(arp_pckt->hardware_type);
    arp_pckt->protocol_type = ntohs(arp_pckt->protocol_type);
    arp_pckt->opcode = ntohs(arp_pckt->opcode);

    if (arp_pckt->hardware_type != ARP_ETHERNET) {
        printf("Unsupported HW type, skipping packet\n\n");
     }

     if (arp_pckt->protocol_type != ARP_IPV4) {
         printf("Unsupported protocol, skippping packet\n\n");
     }

     if(arp_pckt->opcode == ARP_REQUEST){
       printf("arp_request\n--------\n");
       print_arp_packet();
       arp_pckt->sip = ntohl(arp_pckt->sip);
       arp_pckt->dip = ntohl(arp_pckt->dip);
       arp_reply();
       exit(0);	
     }
}

// modifies the packet so that it just swaps sip and dip and sets the smac with our mac
// as if we are the machine having dip

void arp_reply(){

   // reply
  memcpy(arp_pckt->dmac, arp_pckt->smac, 6);
  memset(arp_pckt->smac, 0, 6);

  uint32_t tmp = arp_pckt->dip;
  arp_pckt->dip = arp_pckt->sip;
  arp_pckt->sip = tmp;

  arp_pckt->opcode = ARP_REPLY;

  arp_pckt->opcode = htons(arp_pckt->opcode);
  arp_pckt->hardware_type = htons(arp_pckt->hardware_type);
  arp_pckt->protocol_type = htons(arp_pckt->protocol_type);


  arp_pckt->sip = htonl(arp_pckt->sip);
  arp_pckt->dip = htonl(arp_pckt->dip);

  ethernet_packet->ethertype = htons(ETH_P_ARP);
  printf("Arp reply \n-------\n");
  print_arp_packet();
  printf("\n\n");
  int bytes = tap_write(ethernet_packet,ethernet_len);

  printf("printed %d bytes into tap device\n\n",bytes);
}
