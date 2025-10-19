#include "graph.h"
#include "CommandParser/libcli.h"



extern graph_t *build_first_topo();
extern int send_pkt_out(char *pkt, unsigned int pkt_size, interface_t* interface);

graph_t* topo = NULL;
extern void nw_init_cli();

int main(int argc, char **argv){

	nw_init_cli();
	
	topo = build_first_topo();
	
	/*Time for receiver to start*/
	sleep(2);

	node_t* snode = get_node_by_node_name(topo, "R0_re");
	interface_t* oif = get_node_if_by_name(snode, "eth0/0");

	char msg[] = "Hello, how are you\0";
	send_pkt_out(msg, strlen(msg), oif);

	
	start_shell();

	return 0;
}
