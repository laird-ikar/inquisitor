/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:59:30 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/24 16:42:49 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/inquisitor.hpp"

// pcap_t* handle; // Session handle

// int main(int argc, char *argv[])
// {
// 	if (argc != 5)
// 	{
// 		cout << "Usage: ./inquisitor IP-src MAC-src IP-target MAC-target" << endl;
// 		return (1);
// 	}
// 	// if (regex_match(argv[1], regex("([0-9]{1,3}\\.){3}[0-9]{1,3}")) == false)
// 	// {
// 	// 	cout << "Invalid IP address for IP-src" << endl;
// 	// 	return (1);
// 	// }
// 	// if (regex_match(argv[2], regex("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})")) == false)
// 	// {
// 	// 	cout << "Invalid MAC address for MAC-src" << endl;
// 	// 	return (1);
// 	// }
// 	// if (regex_match(argv[3], regex("([0-9]{1,3}\\.){3}[0-9]{1,3}")) == false)
// 	// {
// 	// 	cout << "Invalid IP address for IP-target" << endl;
// 	// 	return (1);
// 	// }
// 	// if (regex_match(argv[4], regex("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})")) == false)
// 	// {
// 	// 	cout << "Invalid MAC address for MAC-target" << endl;
// 	// 	return (1);
// 	// }

// 	string ip_src = argv[1];
// 	string mac_src = argv[2];
// 	string ip_target = argv[3];
// 	string mac_target = argv[4];
	
// 	char errbuf[PCAP_ERRBUF_SIZE]; // Error buffer
// 	signal(SIGINT, signalHandler); 	// Handle signals (CTRL+C)
// 	/*	
// 	*	Open device for live capture on device eth0
// 	*	read a maximun of BUFSIZ bytes
// 	*	in promiscuous mode
// 	* 	wait until a packet is available
// 	* 	and store possible error message in errbuf
// 	*/
// 	if ((handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf)) == NULL)
// 	{
// 		cout << "Error while opening device for live capture on eth0: " << errbuf << endl;
// 		return (1);
// 	}
// 	const char* filter = ""; // Filter expression
// 	struct bpf_program fp; // Compiled filter expression
// 	/*	
// 		*	Compile and apply filter on the handle
// 		*	optimizing the filter expression (may lengthen the time to compile it)
// 		*	without specifying the netmask
// 		*/
// 	if (pcap_compile(handle, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) == -1) {
// 		cerr << "Error while compiling filter: " << pcap_geterr(handle) << endl;
// 		return 1;
// 	}
// 	if (pcap_setfilter(handle, &fp) == -1) {
// 		cerr << "Error while setting filter: " << pcap_geterr(handle) << endl;
// 		return 1;
// 	}

// 	// Store original ARP tables
// 	vector<ArpEntry> originalArpTables = storeArpTables();

// 	cout << "*****\tCapturing packets...\t*****" << endl << endl;
// 	while (1)
// 	{
// 		pcap_loop(handle, 1, callback_function, NULL); // Start capturing packets by calling callback_function for each packet, without stopping
// 	}
	
// 	return 0;
// }

// void signalHandler(int signum)
// {
//     cout << "*****\tTermination signal received. Stopping packet capture . . .\t*****" << endl;
//    // Clean everything, restore ARP tables, close the handle, exit properly, ...
// 	pcap_close(handle);
// 	//TODO:
// 	// - restore ARP tables
// 	// - exit properly/clean everything ?
// 	exit(0) ;
// }

// void callback_function(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packetData)
// {
// 	cout << "Packet captured" << endl;
// 	cout << "\tPacket length: " << pkthdr->len << endl;
// 	cout << "\tNumber of bytes: " << pkthdr->caplen << endl;
// 	cout << "\tReceived time: " << ctime((const time_t*)&pkthdr->ts.tv_sec) << endl;
// 	cout << "\tPacket data:" << packetData << endl << endl;



// 	// Check if the packet is an ARP packet
//     const struct ether_header* ethHeader = (struct ether_header*)packetData;
//     if (ntohs(ethHeader->ether_type) != ETHERTYPE_ARP)
// 	{
// 		cout << "Not an ARP packet" << endl;
//         return;
// 	}

// 	// Destination address of the ARP packet is stored from offset 0x1C
//     const unsigned char* targetMac = packetData + 0x1C;


// 	// Check if target is in dest or source and adapt the rest

// 	// Edit the destination MAC address of the ARP packet
//     unsigned char newMac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};  // Replace by the new MAC address
//     std::memcpy((void*)targetMac, (void*)newMac, 6);

//     std::cout << "Paquet ARP modifié : " << std::endl;
//     std::cout << "Adresse MAC de destination : " << ether_ntoa((const struct ether_addr*)targetMac) << std::endl;



// 	// // Réenvoyer le paquet ARP modifié
//     // pcap_t* handleEdited = (pcap_t*)userData;
//     // if (pcap_sendpacket(handleEdited, packetData, pkthdr->len) != 0) {
//     //     std::cerr << "Erreur lors de l'envoi du paquet ARP modifié : " << pcap_geterr(handle) << std::endl;
//     // } else {
//     //     std::cout << "Paquet ARP modifié réenvoyé avec succès !" << std::endl;
//     // }


// 	//TODO: 
// 	// - on ARP request/reply, check if it is for the target IP/source IP
// 	// - if it is for the source/target IP, change the target/source MAC address to the source/target MAC address, then send the packet back to the network
// }

// vector<ArpEntry> storeArpTables() {
//     vector<ArpEntry> arpEntries;

//     ifstream arpFile("/proc/net/arp");
//     if (!arpFile) {
//         cerr << "Erreur lors de la lecture du fichier ARP" << endl;
//         return arpEntries;
//     }

//     // Ignore the first line (column titles)
//     string line;
//     getline(arpFile, line);

//     while (getline(arpFile, line)) {
//         ArpEntry entry;
//         istringstream iss(line);

//        	// Read all IP and MAC addresses entries
//         if (!(iss >> entry.ip >> ws >> ws >> ws >> entry.mac)) {
//             cerr << "Erreur lors de la lecture d'une entrée ARP" << endl;
//             continue;
//         }
//         arpEntries.push_back(entry);
//     }
//     arpFile.close();

//     return arpEntries;
// }


void packetHandler(unsigned char* userData, const struct pcap_pkthdr* pkthdr, const unsigned char* packetData) {
    std::cout << "Packet captured" << std::endl;
    std::cout << "\tPacket length: " << pkthdr->len << std::endl;
    std::cout << "\tNumber of bytes: " << pkthdr->caplen << std::endl;
    std::cout << "\tReceived time: " << ctime((const time_t*)&pkthdr->ts.tv_sec) << std::endl;
	//afficher ether type
	std::cout << "\tEther type: " << ntohs(((struct ether_header*)packetData)->ether_type) << std::endl;
	std::cout << (struct ether_header*)packetData << endl;
    // Vous pouvez également afficher d'autres informations du paquet si nécessaire
    std::cout << std::endl;
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE]; // Tampon pour les erreurs
    pcap_t* handle;

    // Ouvrir le dispositif de capture
    handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);  // Remplacez "eth0" par le nom de votre interface réseau

    if (handle == NULL) {
        std::cerr << "Erreur lors de l'ouverture du dispositif de capture: " << errbuf << std::endl;
        return 1;
    }

    // Capturer les paquets en boucle et appeler la fonction de gestion de paquets pour les traiter
    pcap_loop(handle, -1, packetHandler, NULL);

    pcap_close(handle);
    return 0;
}