#include "graph.h"
#include "comm.h"

extern void network_start_pkt_receiver_thread(graph_t* topo);

graph_t * build_linear_topo(){

	graph_t* topo = create_new_graph("Linear Topo");

	node_t* H1 = create_graph_node(topo, "H1");
	node_t* H2 = create_graph_node(topo, "H2");
	node_t* H3 = create_graph_node(topo, "H3");

	insert_link_between_two_nodes(H1, H2, "eth0/1", "eth0/2", 1);
	insert_link_between_two_nodes(H2, H3, "eth0/3", "eth0/4", 1);

	node_set_loopback_address(H1, "122.1.1.1");
	node_set_loopback_address(H2, "122.1.1.2");
	node_set_loopback_address(H3, "123.1.1.3");

	node_set_intf_ip_address(H1, "eth0/1", "10.1.1.1", 24);
	node_set_intf_ip_address(H2, "eth0/2", "10.1.1.2", 24);
	node_set_intf_ip_address(H2, "eth0/3", "20.1.1.2", 24);
	node_set_intf_ip_address(H3, "eth0/4", "20.1.1.1", 24);

	network_start_pkt_receiver_thread(topo);

	return topo;
}
