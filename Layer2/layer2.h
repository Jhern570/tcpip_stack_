#ifndef __LAYER2__
#define __LAYER2__

#include <stdlib.h>
#include <string.h>
#include "../net.h"
#include "../gluethread/glthread.h"
#include "../graph.h"

#define ETH_HDR_SIZE_EXCL_PAYLOAD	\
	(sizeof(ethernet_hdr_t) - sizeof(((ethernet_hdr_t*)0)->payload))

#define ETH_FCS(eth_hdr_ptr,payload_size) \
	(*(unsigned int*)(((char*)(((ethernet_hdr_t*)eth_hdr_ptr)->payload) + payload_size)))	


#pragma pack (push,1)
typedef struct ethernet_hdr_{
	
	mac_add_t dst_mac;
	mac_add_t src_mac;
	short type;
	char payload[248];
	unsigned int FCS;

}ethernet_hdr_t;
#pragma pack(pop)


static inline void SET_COMMON_ETH_FCS(ethernet_hdr_t* eth_hdr, unsigned int pkt_siz, unsigned int new_fcs){

	;
}


static inline ethernet_hdr_t* ALLOC_ETH_HDR_WITH_PAYLOAD(char* pkt, unsigned int pkt_size){

	char *temp = calloc(1, pkt_size);
	memcpy(temp, pkt, pkt_size);
	
	ethernet_hdr_t* eth_hdr = (ethernet_hdr_t*)(pkt - ETH_HDR_SIZE_EXCL_PAYLOAD);

	memset((char*)eth_hdr, 0 , ETH_HDR_SIZE_EXCL_PAYLOAD);
	memcpy(eth_hdr->payload, temp, pkt_size);

	SET_COMMON_ETH_FCS(eth_hdr, pkt_size, 0);
	free(temp);

	return eth_hdr;
 
}

static inline bool_t l2_frame_recv_qualify_on_interface(interface_t* interface, ethernet_hdr_t* ethernet_hdr){
	
	if(!IS_INT_L3_MODE(interface)) return FALSE;

	if(memcmp(IF_MAC(interface), ethernet_hdr->dst_mac.mac, sizeof(mac_add_t)) == 0) return TRUE;

	if(IS_MAC_BROADCAST_ADDR(ethernet_hdr->dst_mac.mac)) return TRUE;

	return FALSE;
}

#endif

