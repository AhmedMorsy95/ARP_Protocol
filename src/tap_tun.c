#include "../headers/includes.h"
#include "../headers/tap_tun.h"
#include "../headers/ethernet.h"

static int tap_fd;
char *tapaddr = "10.0.0.1";
char tap_buffer[buffer_size];

int tap_alloc(char *dev, int flags) {

  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";

  /* Arguments taken by the function:
   *
   * char *dev: the name of an interface (or '\0'). MUST have enough
   *   space to hold the interface name if '\0' is passed
   * int flags: interface flags (eg, IFF_TUN etc.)
   */
   /* open the clone device */
   if( (fd = open(clonedev, O_RDWR)) < 0 ) {
     printf("Cannot open TUN/TAP dev\n");
     return fd;
   }
   /* preparation of the struct ifr, of type "struct ifreq" */
   memset(&ifr, 0, sizeof(ifr));

   ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

   if (*dev) {
     strncpy(ifr.ifr_name, dev, IFNAMSIZ);
     printf("opening device called : %s\n",dev);
   }

   /* try to create the device */
   if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) { // control device
     close(fd);
     printf("ioctl failed and returned errno %s \n",strerror(errno));
     return err;
   }

  /* if the operation was successful, write back the name of the
   * interface to the variable "dev", so the caller can know
   * it. Note that the caller MUST reserve space in *dev (see calling
   * code below) */
  strcpy(dev, ifr.ifr_name);

  /* this is the special file descriptor that the caller will use to talk
   * with the virtual interface */
  return fd;
}

void tap_init(){
  char tun_name[10];
  strcpy(tun_name, "tap1");
  tap_fd = tap_alloc(tun_name, IFF_TAP|IFF_NO_PI); // flags, IFF_NO_PI - Do not provide packet information
  if(tap_fd < 0){
   perror("Allocating interface");
   exit(1);
  }
}

/// reads from tap device into buf and returns how many bytes it read
int tap_read(){
  int nread = read(tap_fd,tap_buffer,buffer_size);
   if(nread < 0) {
     perror("Reading from interface");
     close(tap_fd);
     exit(1);
   }
   printf("read from tap %d\n",nread);
   return ethernet_len = nread;
}

int tap_write(char *buf,int len){
   return write(tap_fd, (char*)buf, len);
}
