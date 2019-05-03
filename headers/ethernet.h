#include <stdint.h>
#define ETH_P_ARP	0x0806		/* Address Resolution packet	*/
#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/

struct ethernet_header
{
    unsigned char dmac[6];
    unsigned char smac[6];
    uint16_t ethertype;
    unsigned char payload[];
} __attribute__((packed));

extern struct ethernet_header *ethernet_packet;
extern int ethernet_len;

void parse_ethernet();
void handle_packet();
/* packed avoids padding the data which may add meaningless bytes
If you want to ensure that your structures have the same size on all processors,
 the packed attribute is how you tell gcc.

example:

struct s {
   char aChar;
   int    anInt;
};
A processor that aligns on eight-byte boundaries may compile this so that aChar
is in the first byte, followed by seven bytes of unused space, then starting anInt in
the ninth byte.

*/
