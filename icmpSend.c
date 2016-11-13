#include <xinu.h>

#define ICMP_HEADER_LEN 4

struct icmpPkt {
  uchar type;
  uchar code;
  ushort chksum;
  int data;
};


syscall icmpSend(struct ethergram *pkt, uchar type, uchar code, int datalen,struct netaddr *src, struct netaddr *dst) {
  struct ipgram *ip = NULL; //need the payload of ipgram to set as icmp
  //struct ethergram *egram = NULL; //not sure if we need this
  uchar *buf;
  uchar srcMac[ETH_ADDR_LEN];
  int i;
  buf = (uchar *)malloc(PKTSZ);
  
  control(ETH0, ETH_CTRL_GET_MAC, (ulong) srcMac, 0);
  
  pkt->src = *srcMac; //incompatible types when assigning to type ‘uchar[6]’ from type ‘uchar *’
  
  for(i = 0; i < ETH_ADDR_LEN; i++)
  {
    pkt->dst[i] = 0XFF;
  }
  pkt->type = htons(ETYPE_IPv4);
  pkt->data = ip; //incompatible types when assigning to type ‘char[1]’ from type ‘struct ipgram *’
  
  ip->ver_ihl = (uchar)(IPv4_VERSION << 4);
  ip->ver_ihl += IPv4_HDR_LEN; //may need IPv4_MAX_HDRLEN
  ip->tos = IPv4_TOS_ROUTINE; //service type
  ip->len = IPv4_HDR_LEN; // + data length
  ip->id = 0;
  ip->flags_froff = 0;
  ip->ttl = IPv4_TTL;
  ip->proto = IPv4_PROTO_ICMP;
  if (NULL == src->type) {    //dereferencing pointer to incomplete type
    memcpy(ip->src, pkt->src, IPv4_ADDR_LEN);
  } else {
    memcpy(ip->src, src->addr, IPv4_ADDR_LEN);   //dereferencing pointer to incomplete type
  }
  memcpy(ip->dst, dst->addr, IPv4_ADDR_LEN);      //dereferencing pointer to incomplete type
  
 // ip->chksum = 0;
 // ip->chksum = checksum((uchar *)ip, IPv4_HDR_LEN);
  
  //write(ETH0, buf, PKTSZ)
  
  
  struct icmpPkt *icmp = NULL;
  icmp->type = type;
  icmp->code = code;
  icmp->chksum = 0;
  icmp->chksum = netChksum((uchar *)icmp, datalen + ICMP_HEADER_LEN);  //implicit declaration of function ‘netChksum’
  
  ip->opts = icmp;    //incompatible types when assigning to type ‘uchar[1]’ from type ‘struct icmpPkt *’
  
  icmp->data = 3;
  
  memcpy(buf, &pkt, PKTSZ);
  
  if (NULL == pkt) {
    return SYSERR;
  }
  
  
  if ((write(ETH0, buf, PKTSZ)) == SYSERR) {
    fprintf(CONSOLE, "%s\n", "Packet didn't send");
  } else {
    fprintf(CONSOLE, "%s\n", "Sent ethergram packet from icmpSend");
  }
  //send packet with number in it, have the other machine send back the number, right before you send the packet, right after you receive the response packet, record the time and subtract the two
  
  
  free(buf);
  
  
  return OK;
  
}
