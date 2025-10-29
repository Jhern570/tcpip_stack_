#ifndef __UTILS__
#define __UTILS__

#include <stdint.h>

#define MAC_MAX_SIZE	6

#define IS_MAC_BROADCAST_ADDR(mac)	\
	(mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF &&	\
	 mac[3] == 0xFF && mac[4] == 0xFF && mac[5] == 0xFF)

void apply_mask(char* prefix, char mask, char *str_prefix);

void layer2_fill_with_broadcast_mac(char* mac_array);

void tcp_ip_from_n_to_p(unsigned int ip_addr,
        char *output_buffer);

unsigned int tcp_ip_from_p_to_n(char *ip_addr);



#endif
