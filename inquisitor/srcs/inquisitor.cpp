/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquisitor.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:59:30 by bguyot            #+#    #+#             */
/*   Updated: 2023/05/21 10:32:26 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/inquisitor.hpp"

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

	
}