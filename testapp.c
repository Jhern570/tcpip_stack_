#include <stdio.h>
#include "graph.h"
#include "CommandParser/libcli.h"


//extern functions of topologies build
extern graph_t *build_first_topo();
extern graph_t *build_linear_topo();


//extern functions from comm.c
extern int send_pkt_out(char *pkt, unsigned int pkt_size, interface_t* interface);
extern int send_pkt_flood(node_t* node, interface_t* exempted_interface, char* pkt, unsigned int pkt_size);

//extern function from ./CommandParser
extern void nw_init_cli();

graph_t* topo = NULL;

int main(int argc, char **argv){

	printf("Starting CLI\n");
	nw_init_cli();
		
	printf("Building topo...\n");
	topo = build_linear_topo();

	if(!topo){
		printf("Error : Could not create topology!\n");
		return 0;
	}

	/*Time for receiver to start*/
	//sleep(2);

	//node_t* snode = get_node_by_node_name(topo, "R0_re");
	//interface_t* oif = get_node_if_by_name(snode, "eth0/0");

	//char msg[] = "Hello, how are you\0";
	//send_pkt_out(msg, strlen(msg), oif);

	//send_pkt_flood(snode, oif, msg, strlen(msg));
	printf("Running shell\n");
	start_shell();

	return 0;
}
