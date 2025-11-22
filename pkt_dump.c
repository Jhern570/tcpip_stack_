#ifndef __PKT_DUMP__
#define __PKT_DUMP__

#include "Layer2/layer2.h"
#include <stdio.h>
#include <arpa/inet.h>

void pkt_dump(ethernet_hdr_t* ethernet_hdr, unsigned int pkt_size){

	vlan_8021q_hdr_t* vlan_8021q_hdr = is_packet_vlan_tagged(ethernet_hdr);

	arp_hdr_t* arp_hdr;
	
	if(vlan_8021q_hdr){
	
		vlan_ethernet_hdr_t* vlan_ethernet_hdr = (vlan_ethernet_hdr_t*)ethernet_hdr;

		arp_hdr_t* arp_hdr = (arp_hdr_t*)ethernet_hdr->payload;

        	mac_add_t dst_mac = vlan_ethernet_hdr->dst_mac;
        	mac_add_t src_mac = vlan_ethernet_hdr->src_mac;

        	printf("VLAN Ethernet header:\n"
                	"\tdst MAC address: %u:%u:%u:%u:%u:%u\n"
                	"\tsrc MAC address: %u:%u:%u:%u:%u:%u\n"
                	"\ttype:          : %hu\n",
                	dst_mac.mac[0], dst_mac.mac[1], dst_mac.mac[2], dst_mac.mac[3], dst_mac.mac[4], dst_mac.mac[5],
                	src_mac.mac[0], src_mac.mac[1], src_mac.mac[2], src_mac.mac[3], src_mac.mac[4], src_mac.mac[5],
                	vlan_ethernet_hdr->type);

        	dst_mac = arp_hdr->dst_mac;
        	src_mac = arp_hdr->src_mac;

        	unsigned int dst_ip_int = arp_hdr->dst_ip;
        	unsigned int src_ip_int = arp_hdr->src_ip;

        	char* dst_ip[16], src_ip[16];

        	if(inet_ntop(AF_INET, &dst_ip_int, &dst_ip, 16) == NULL &&
           	  inet_ntop(AF_INET, &src_ip_int, &src_ip, 16) == NULL){
              	
			perror("Error : ntop could not convert to ip address\n");
        	}

        	dst_ip[15] = '\0';
        	src_ip[15] = '\0';



        	printf("\n");

        	printf("ARP header:\n"
                	"\thw type        : %hu\n"
                	"\tproto type     : %hu\n"
                	"\thw addr len    : %d\n"
                	"\tproto addr len : %d\n"
                	"\top code        : %hu"
                	"\tsrc MAC address: %u:%u:%u:%u:%u:%u\n"
                	"\tsrc IP address : %s\n"
                	"\tdst MAC address: %u:%u:%u:%u:%u:%u\n"
                	"\tdst IP address : %s\n",
                	arp_hdr->hw_type, arp_hdr->proto_type, arp_hdr->hw_addr_len,
                	arp_hdr->proto_addr_len, arp_hdr->op_code,
                	src_mac.mac[0], src_mac.mac[1], src_mac.mac[2], src_mac.mac[3], src_mac.mac[4], src_mac.mac[5],
                	src_ip,
                	dst_mac.mac[0], dst_mac.mac[1], dst_mac.mac[2], dst_mac.mac[3], dst_mac.mac[4], dst_mac.mac[5],
                	dst_ip);
	
	
	}else{
		arp_hdr = (arp_hdr_t*)ethernet_hdr->payload;

		mac_add_t dst_mac = ethernet_hdr->dst_mac;
		mac_add_t src_mac = ethernet_hdr->src_mac;

		printf("Ethernet header:\n"
	        	"\tdst MAC address: %u:%u:%u:%u:%u:%u\n"
			"\tsrc MAC address: %u:%u:%u:%u:%u:%u\n"
			"\ttype:          : %hu\n",
			dst_mac.mac[0], dst_mac.mac[1], dst_mac.mac[2], dst_mac.mac[3], dst_mac.mac[4], dst_mac.mac[5],
			src_mac.mac[0], src_mac.mac[1], src_mac.mac[2], src_mac.mac[3], src_mac.mac[4], src_mac.mac[5],
			ethernet_hdr->type);

		dst_mac = arp_hdr->dst_mac;
		src_mac = arp_hdr->src_mac;

		unsigned int dst_ip_int = arp_hdr->dst_ip;
		unsigned int src_ip_int = arp_hdr->src_ip;

		char* dst_ip[16], src_ip[16];
	
		if(inet_ntop(AF_INET, &dst_ip_int, &dst_ip, 16) == NULL &&
	   	  inet_ntop(AF_INET, &src_ip_int, &src_ip, 16) == NULL){
	      	
			perror("Error : ntop could not convert to ip address\n");
		}
	
		dst_ip[15] = '\0';
		src_ip[15] = '\0';



		printf("\n");

		printf("ARP header:\n"
			"\thw type	  : %hu\n"
			"\tproto type	  : %hu\n"
			"\thw addr len	  : %d\n"
			"\tproto addr len : %d\n"
			"\top code	  : %hu"
			"\tsrc MAC address: %u:%u:%u:%u:%u:%u\n"
			"\tsrc IP address : %s\n"
			"\tdst MAC address: %u:%u:%u:%u:%u:%u\n"
			"\tdst IP address : %s\n",
			arp_hdr->hw_type, arp_hdr->proto_type, arp_hdr->hw_addr_len,
			arp_hdr->proto_addr_len, arp_hdr->op_code,
			src_mac.mac[0], src_mac.mac[1], src_mac.mac[2], src_mac.mac[3], src_mac.mac[4], src_mac.mac[5],
			src_ip,
			dst_mac.mac[0], dst_mac.mac[1], dst_mac.mac[2], dst_mac.mac[3], dst_mac.mac[4], dst_mac.mac[5],
			dst_ip);

	}
	
}

#endif
