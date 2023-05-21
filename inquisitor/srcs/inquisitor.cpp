/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:59:30 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/21 13:24:00 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/inquisitor.hpp"

// Global boolean to stop the capture and close the handle
bool keepCapturing = true;

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		std::cout << "Usage: ./inquisitor IP-src MAC-src IP-target MAC-target" << std::endl;
		return (1);
	}
	std::string ip_src = argv[1];
	std::string mac_src = argv[2];
	std::string ip_target = argv[3];
	std::string mac_target = argv[4];


	pcap_t* handle; // Session handle
	char errbuf[PCAP_ERRBUF_SIZE]; // Error buffer

	// Open device for live capture on device eth0, read a maximun of BUFSIZ bytes, in promiscuous mode, wait until a packet is available, and store possible error message in errbuf
	if ((handle = pcap_open_live("eth0", BUFSIZ, 1, 0, errbuf)) == nullptr)
	{
		std::cout << "Error: " << errbuf << std::endl;
		return (1);
	}


	const char* filter = "arp"; // Filter expression
	struct bpf_program fp; // Compiled filter expression

	// Compile and apply filter on the handle, optimizing the filter expression (may lengthen the time to compile it), without specifying the netmask
	if (pcap_compile(handle, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) == -1) {
		std::cerr << "Error compiling filter: " << pcap_geterr(handle) << std::endl;
		return 1;
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		std::cerr << "Error setting filter: " << pcap_geterr(handle) << std::endl;
		return 1;
	}

	// Handle signals (CTRL+C)
    std::signal(SIGINT, signalHandler);


	pcap_dispatch(handle, 0, callback_function, nullptr);



	// Clean everything, restore ARP tables, close the handle, exit properly, ...
	pcap_close(handle);
	//TODO: the rest
}


void signalHandler(int signum)
{
    std::cout << "Termination signal received. Stopping packet capture." << std::endl;
    keepCapturing = false;
}

void callback_function(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packetData)
{
	std::cout << "Packet captured." << std::endl;
}