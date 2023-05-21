/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:01:32 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/21 13:24:00 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <pcap.h>
#include <stdio.h>
#include <csignal>

void signalHandler(int signum);
void callback_function(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packetData);