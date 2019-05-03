#include <stdint.h>

#define ARP_ETHERNET    0x0001
#define ARP_IPV4        0x0800
#define ARP_REQUEST     0x0001
#define ARP_REPLY       0x0002

extern struct arp_packet *arp_pckt;

struct arp_packet
{
    uint16_t hardware_type; // link layer type used -> ethernet 0 x 0001
    uint16_t protocol_type; // indicates the protocol type for which arp request is intended  -> IPv4 0x0800
    // who is the protocol who issues this arp ?
    unsigned char hardware_size; // size of hardware field 6 bytes for mac addr
    unsigned char protocol_size; // size of IP addresses 4 bytes for IP addr
    uint16_t opcode; // type of arp message request,relpy,rarp request,rarp reply
    unsigned char smac[6];
    uint32_t sip;
    unsigned char dmac[6]; /// this is the filed we would like to determine
    uint32_t dip;
} __attribute__((packed));

void parse_arp();
void arp_reply();
