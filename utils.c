#include "utils.h"
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
void apply_mask(char* prefix, char mask, char *str_prefix){

	uint32_t binary_prefix = 0;
	uint32_t subnet_mask = 0xFFFFFFFF;

	if(mask == 32){
		strncpy(str_prefix, prefix, 16);
		str_prefix[15] = '\0';
		return;
	}

	inet_pton(AF_INET, prefix, &binary_prefix);

	binary_prefix = htonl(binary_prefix);

	subnet_mask = subnet_mask << (32 - mask);

	binary_prefix = binary_prefix & subnet_mask;

	binary_prefix = htonl(binary_prefix);

	inet_ntop(AF_INET, &binary_prefix, str_prefix, 16);
	str_prefix[15] = '\0';


}

void layer2_fill_with_broadcast_mac(char* mac_addr){
	
	for(int i = 0; i < MAC_MAX_SIZE; i++){
		mac_addr[i] = 0xFF;
	}
	
}

void tcp_ip_from_n_to_p(unsigned int ip_addr,
        char *output_buffer){

    memset(output_buffer, 0, 16);
    ip_addr = htonl(ip_addr);
    //ip_addr = ntohl(ip_addr);
    inet_ntop(AF_INET, &ip_addr, output_buffer, 16);
    output_buffer[15] = '\0';
}

unsigned int tcp_ip_from_p_to_n(char *ip_addr){

    unsigned int binary_prefix = 0;
    inet_pton(AF_INET, ip_addr, &binary_prefix);
    binary_prefix = htonl(binary_prefix);
    return binary_prefix;
}

