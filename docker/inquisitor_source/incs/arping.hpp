#pragma once

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <cstring>
#include <unistd.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARP_REQUEST 1
#define ETHER_TYPE_ARP 0x0806

// typedef struct		s_arp_header {
//     unsigned short	hardware_type;
//     unsigned short	protocol_type;
//     unsigned char	hardware_len;
//     unsigned char	protocol_len;
//     unsigned short	opcode;
//     unsigned char	sender_mac[6];
//     unsigned char	sender_ip[4];
//     unsigned char	target_mac[6];
//     unsigned char	target_ip[4];
// }	t_arp_header;

typedef struct	s_arping_args {
	std::string receiver_ip;
	std::string sender_ip;
	std::string sender_mac;
}				t_arping_args;

/** 
 *	@brief send arp packet (spoofing)
 *	@param receiver_ip ip of the recever
 *	@param sender_ip ip of the sender
 *	@return 0 on success, -1 on error
 */
void arping(
	const t_arping_args &args
	);