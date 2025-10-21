#include "layer2.h"

void layer2_frame_recv(node_t* node, interface_t* interface, char* pkt, unsigned int pkt_size) {
	
	//Entry point into TCP/IP stack from bottom
	

}


void init_arp_table(arp_table_t** arp_table){
	*arp_table = calloc(1,sizeof(arp_table_t));

	init_glthread(&((*arp_table)->arp_entries));
}
