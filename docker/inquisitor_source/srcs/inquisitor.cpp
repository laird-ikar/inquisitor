/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:59:30 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/21 17:01:37 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/inquisitor.hpp"

// Global boolean to stop the capture and close the handle
// bool keepCapturing = true;
pcap_t* handle; //NOTE: Session handle


int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Usage: ./inquisitor IP-src MAC-src IP-target MAC-target" << endl;
		return (1);
	}
	//TODO: check if IP and MAC addresses are valid
	string ip_src = argv[1];
	string mac_src = argv[2];
	string ip_target = argv[3];
	string mac_target = argv[4];
	
	char errbuf[PCAP_ERRBUF_SIZE]; //NOTE: Error buffer
	signal(SIGINT, signalHandler); 	//NOTE: Handle signals (CTRL+C)
	/*	NOTE:
	*	Open device for live capture on device eth0
	*	read a maximun of BUFSIZ bytes
	*	in promiscuous mode
	* 	wait until a packet is available
	* 	and store possible error message in errbuf
	*/
	if ((handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf)) == nullptr)
	{
		cout << "Error while opening device for live capture on eth0: " << errbuf << endl;
		return (1);
	}
	const char* filter = ""; //NOTE: Filter expression
	struct bpf_program fp; //NOTE: Compiled filter expression
	/*	NOTE:
		*	Compile and apply filter on the handle
		*	optimizing the filter expression (may lengthen the time to compile it)
		*	without specifying the netmask
		*/
	if (pcap_compile(handle, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) == -1) {
		cerr << "Error while compiling filter: " << pcap_geterr(handle) << endl;
		return 1;
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		cerr << "Error while setting filter: " << pcap_geterr(handle) << endl;
		return 1;
	}
	while (1)
	{
		cout << "Capturing packets..." << endl;
		pcap_dispatch(handle, 1, callback_function, nullptr);//NOTE: Start capturing packets by calling callback_function for each packet
	}
	
	return 0;
}

void signalHandler(int signum)
{
    cout << "Termination signal received. Stopping packet capture . . ." << endl;
   //NOTE: Clean everything, restore ARP tables, close the handle, exit properly, ...
	pcap_close(handle);
	//TODO:
	// - restore ARP tables
	// - exit properly/clean everything ?
	return ;
}

void callback_function(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packetData)
{
	cout << "Packet captured" << endl;
	cout << "\tPacket length: " << pkthdr->len << endl;
	cout << "\tNumber of bytes: " << pkthdr->caplen << endl;
	cout << "\tReceived time: " << ctime((const time_t*)&pkthdr->ts.tv_sec) << endl;
	cout << "Packet data:" << packetData << endl << endl;

	//TODO: 
	//XXX: - save original ARP tables when first packet is captured
	// - check if packet is an ARP request/reply
	// - on ARP request/reply, check if it is for the target IP/source IP
	// - if it is for the source/target IP, change the target/source MAC address to the source/target MAC address, then send the packet back to the network
}