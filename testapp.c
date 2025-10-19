#include "graph.h"
#include "CommandParser/libcli.h"



extern graph_t *build_first_topo();

//extern functions from comm.c
extern int send_pkt_out(char *pkt, unsigned int pkt_size, interface_t* interface);
extern int send_pkt_flood(node_t* node, interface_t* exempted_interface, char* pkt, unsigned int pkt_size);

//extern function from ./CommandParser
extern void nw_init_cli();

graph_t* topo = NULL;

int main(int argc, char **argv){

	nw_init_cli();
	
	topo = build_first_topo();
	
	/*Time for receiver to start*/
	sleep(2);

	node_t* snode = get_node_by_node_name(topo, "R0_re");
	interface_t* oif = get_node_if_by_name(snode, "eth0/0");

	char msg[] = "Hello, how are you\0";
	send_pkt_out(msg, strlen(msg), oif);

	send_pkt_flood(snode, oif, msg, strlen(msg));
	start_shell();

	return 0;
}
