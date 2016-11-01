#include <xinu.h>




syscall icmpEchoRequest(struct netaddr *dst, ushort id, ushort seq) {
  
  struct packet *pkt;
  struct icmpEcho *echo;
  int result;
  struct netaddr src;
  
  pkt->len = sizeof(struct icmpEcho);
  
  result = icmpSend(pkt, ICMP_ECHO, 0, sizeof(struct icmpEcho), &src, dst);
  
  return result;
}



