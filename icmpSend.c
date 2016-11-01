#include <xinu.h>

syscall icmpSend(struct ethergram *pkt, uchar type, uint datalen,struct netaddr *src, struct netaddr *dst) {
  struct ipgram *ip = NULL; //need the payload of ipgram to set as icmp
  uchar *icmp = NULL;
  
  ip = pkt->data;
  
  ip->ver_ihl = (uchar)(IPv4_VERSION << 4);
  ip->ver_ihl += IPv4_HDR_LEN; //may need IPv4_MAX_HDRLEN
  ip->tos = IPv4_TOS_ROUTINE; //service type
  ip->len = IPv4_HDR_LEN; // + data length
  ip->id = 0;
  ip->flags_froff = 0;
  ip->ttl = IPv4_TTL;
  ip->proto = IPv4_PROTO_ICMP;
  if (NULL == src->type) {
    memcpy(ip->src, pkt->src, IPv4_ADDR_LEN);
  } else {
    memcpy(ip->src, src->addr, IPv4_ADDR_LEN);
  }
  memcpy(ip->dst, dst->addr, IPv4_ADDR_LEN);
  
  ip->chksum = 0;
  ip->chksum = checksum((uchar *)ip, IPv4_HDR_LEN);
  
  //write(ETH0, buf, PKTSZ)
  
  
  
  icmp = ip->opts; //trying to get payload of ipgram
  
  
  
  if (NULL == pkt) {
    return SYSERR;
  }
  
  
  
  
  
}
