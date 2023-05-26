/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:01:32 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/23 16:43:21 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <pcap.h>
#include <stdio.h>
#include <csignal>
#include <regex>
#include <fstream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

using namespace std;

struct ArpEntry {
    std::string ip;
    std::string mac;
};

void signalHandler(int signum);
void callback_function(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packetData);
vector<ArpEntry> storeArpTables();


