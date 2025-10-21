#ifndef __NET__
#define __NET__

#include <memory.h>

typedef struct graph_ graph_t;
typedef struct interface_ interface_t;
typedef struct node_ node_t;

#define IF_MAC(intf_ptr)   	((intf_ptr)->intf_nw_props.mac_add.mac)
#define IF_IP(intf_ptr)   	((intf_ptr)->intf_nw_props.ip_add.ip_addr)

#define NODE_LO_ADDR(node_ptr)	((node_ptr)->node_nw_prop.lb_addr.ip_addr)

#define IS_INT_L3_MODE(intf_ptr) (intf_ptr->intf_nw_props.is_ipadd_config == TRUE)
	


typedef enum{

  FALSE,
  TRUE 
} bool_t;


typedef struct ip_add_{
	char ip_addr[16];
} ip_add_t;

typedef struct mac_add_{
	unsigned char mac[6];
}mac_add_t;

typedef struct node_nw_prop{
	//L3 properties
	bool_t is_lb_addr_config;
	ip_add_t lb_addr; //loopback address of node
}node_nw_prop_t;

static inline void init_node_nw_prop(node_nw_prop_t* node_nw_prop){
	node_nw_prop->is_lb_addr_config = FALSE;
	memset(node_nw_prop->lb_addr.ip_addr, 0, 16);
}

typedef struct intf_nw_props_{
	//L2 properties
	mac_add_t mac_add; //MAC are hard burnt in interface NIC

	//L3 properties
	bool_t is_ipadd_config; //Set to TRUE if ip add is configured, intf operates in L3 mode if ip address is configured on it
	ip_add_t ip_add;
	char mask;
}intf_nw_props_t;

static inline void init_intf_nw_prop(intf_nw_props_t* intf_nw_props){

	memset(intf_nw_props->mac_add.mac, 0, sizeof(intf_nw_props->mac_add.mac));
	intf_nw_props->is_ipadd_config = FALSE;
	memset(intf_nw_props->ip_add.ip_addr, 0, 16);

}

//API to set network properties
bool_t node_set_loopback_address(node_t *node, char* ip_addr);
bool_t node_set_intf_ip_address(node_t *node, char *local_if, char* ip_addr, char mask);
bool_t node_unset_intf_ip_address(node_t *node, char *local_if);


//API for data shift
char* pkt_buffer_shift_right(char* pkt, unsigned int pkt_size, unsigned int total_buffer_size);

interface_t* node_get_matching_subnet_interface(node_t* node, char* ip_addr);


void interface_assign_mac_address(interface_t* interface); 
void convert_ip_from_int_to_str(unsigned int ip_addr, char *output_buffer);

unsigned int convert_ip_from_str_to_int(char *ip_addr);


void dump_nw_graph(graph_t * graph);


#endif
