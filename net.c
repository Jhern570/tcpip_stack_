#include "graph.h"
#include <memory.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned int hash_code(void* ptr, unsigned int size){

	unsigned int value = 0, i = 0;

	char* str = (char*)ptr;

	while(i < size){
		value += *str;
		value *=97;
		str++;
		i++;
	}
	return value;
}

void interface_assign_mac_address(interface_t* interface){

        node_t* node = interface->att_node;

        if(!node) return;
	unsigned int hash_code_val = 0;


        hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
        hash_code_val *= hash_code(interface->if_name, IF_NAME_SIZE);

        memset(IF_MAC(interface), 0, sizeof(IF_MAC(interface)));
        memcpy(IF_MAC(interface), (char*)&hash_code_val, sizeof(unsigned int));
}


/*void interface_assign_mac_address(interface_t* interface){

	memset(IF_MAC(interface), 0, 8);
	strcpy(IF_MAC(interface), interface->att_node->node_name);
        strcat(IF_MAC(interface), interface->if_name);	
}*/

bool_t node_set_loopback_address(node_t* node, char* ip_addr){
	
	assert(ip_addr);

	node->node_nw_prop.is_lb_addr_config = TRUE;
	strncpy(NODE_LO_ADDR(node), ip_addr, 16);
	NODE_LO_ADDR(node)[15] = '\0';

	return TRUE;
}

bool_t node_set_intf_ip_address(node_t* node, char* local_if, char* ip_addr, char mask){
	
	interface_t* interface = get_node_if_by_name(node, local_if);
	if(!interface) assert(0);

	strncpy(IF_IP(interface), ip_addr, 16);
	IF_IP(interface)[15] = '\0';

	interface->intf_nw_props.mask = mask;
	interface->intf_nw_props.is_ipadd_config = TRUE;
	
	return TRUE;
}

char* pkt_buffer_shift_right(char* pkt, unsigned int pkt_size, unsigned int total_buffer_size){


	unsigned int new_size = total_buffer_size - IF_NAME_SIZE;
	char* temp = NULL;

	bool_t need_temp_memory = (pkt_size * 2 > total_buffer_size) ? TRUE : FALSE;


	if(need_temp_memory){
		temp = calloc(1, pkt_size);
		memcpy(temp, pkt, pkt_size);
		memset(pkt, 0, total_buffer_size);
		memcpy(pkt + new_size, temp, pkt_size);
		free(temp);
		return pkt + new_size;
	}

	
	memcpy(pkt + new_size, pkt, pkt_size);
	memset(pkt, 0, pkt_size);

	return pkt + new_size;	

}

bool_t node_unset_intf_ip_address(node_t* node, char* local_if){
	
	return TRUE;
}

interface_t* node_get_matching_subnet_interface(node_t* node, char* ip_addr){

	unsigned int i = 0;
	interface_t* intf;

	char* intf_addr = NULL;
	char mask;
	char intf_subnet[16];
	char subnet2[16];

	for(; i < MAX_INTF_PER_NODE; i++){
		intf = node->intf[i];
		if(!intf) return NULL;

		if(intf->intf_nw_props.is_ipadd_config == FALSE) continue;

		intf_addr = IF_IP(intf);
		mask = intf->intf_nw_props.mask;

		memset(intf_subnet, 0, 16);
		memset(subnet2, 0, 16);

		apply_mask(intf_addr, mask, intf_subnet);
		apply_mask(ip_addr, mask, subnet2);

		if(strncmp(intf_subnet, subnet2, 16) == 0){
			return intf;
		}
	}	
}


void dump_node_nw_props(node_t* node){
	//printf("\nNode name = %s, upd_port_no = %u\n", node->node_name, node->upd_port_number);
	printf("\nNode name =%s\n", node->node_name); 
	//printf("\t node flags : %u", node->node_nw_prop.flags);
	if(node->node_nw_prop.is_lb_addr_config){
		printf("\t	lo addr : %s/32", NODE_LO_ADDR(node));
	}
	printf("\n");
}

void dump_intf_props(interface_t* interface){	
	dump_interface(interface);

	if(interface->intf_nw_props.is_ipadd_config){
		printf("\t IP Addr = %s/%u", IF_IP(interface), interface->intf_nw_props.mask);
		printf("\t MAC : %u:%u:%u:%u:%u:%u", IF_MAC(interface)[0], IF_MAC(interface)[1],
						     IF_MAC(interface)[2], IF_MAC(interface)[3],
						     IF_MAC(interface)[4], IF_MAC(interface)[5]);
	}

	printf("\n");
}

void dump_nw_graph(graph_t* graph){

	node_t* node;
	glthread_t* curr;
	interface_t* interface;
	unsigned int i;

	printf("Topology Name = %s\n", graph->topology_name);

	ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr){
	
		node = graph_glue_to_node(curr);
		dump_node_nw_props(node);
		for(i = 0; i < MAX_INTF_PER_NODE; i++){
			
			interface = node->intf[i];
			if(!interface) {
				break;
			}
			dump_intf_props(interface);		
		}
	}ITERATE_GLTHREAD_END(&graph->node_list, curr);
}
