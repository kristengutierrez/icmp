#include <xinu.h>

syscall icmpEchoReply(struct packet *pkt) {
  struct ipgram *ip;
  struct netaddr src, dst;
  
  ip = (struct ipgram *)pkt->nethdr;
  dst.type = ETYPE_IPv4;
  dst.len = IPv4_ADDR_LEN;
  memcpy(dst.addr, ip->dst, dst.len);
  
  src.type = ETYPE_IPv4;
  src.len = IPv4_ADDR_LEN; //in network.h
  memcpy(src.addr, ip->src, src.len);
  //here's the number of the ping packet you sent me
  return icmpSend(pkt, 0, 0, pkt->len, &dst, &src);
}
