#ifndef __LAYER2__
#define __LAYER2__

#include "../net.h"
#include "../gluthread/glthread.h"

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

}ethernet_hrd_t;
#pragma pack(pop)


static inline void SET_COMMON_ETH_FCS(ethenet_hdr_t* eth_hdr, unsigned int pkt_siz, unsigned int new_fcs){

	;
}


static inline ethernet_hdr_t* ALLOC_ETH_HDR_WITH_PAYLOAD(char* pkt, unsigned int pkt_size){

	char *tmp = calloc(1, pkt_size);
	memcpy(temp, pkt, pkt_size);
	
	ethernet_hdr_t* eth_hdr = (ethernet_hdr_t*)(pkt - ETH_HDR_SIZE_EXCL_PAYLOAD);

	memset((char*)eth_hdr, 0 , ETH_HDR_SIZE_EXCL_PAYLOAD);
	memcpy(eth_hdr->payload, temp, pkt_size);

	SET_COMMON_ETH_FCS(eth_hdr, pkt_size, 0);
	free(tmp);

	return eth_hdr;
 
}

#endif

