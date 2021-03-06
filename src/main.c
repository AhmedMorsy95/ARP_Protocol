#include "../headers/includes.h"
#include "../headers/tap_tun.h"
#include "../headers/ethernet.h"
#include "../headers/debug_functions.h"
#include "../headers/arp.h"

int main(){

  tap_init();

  while(1){
    // read packets from tap device forever
    tap_read();

    // parse the packet
    parse_ethernet();

    // for debugging
    // print_ethernet_packet();

    // handle the packet depeinding on its type
    handle_packet();
  }
  return 0;
}
