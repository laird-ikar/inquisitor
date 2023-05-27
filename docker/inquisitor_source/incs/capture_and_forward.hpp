#pragma once

#include <string>
#include <pcap.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



/**
 * @brief capture packets and forward them
 * @param ip_src ip of the source
 * @param mac_src mac address of the source
 * @param ip_target ip of the target
 * @param mac_target mac address of the target
 */
void capture_and_forward(
	const std::string& ip_src,
	const std::string& mac_src,
	const std::string& ip_target,
	const std::string& mac_target
	);