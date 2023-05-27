#include "../incs/main.hpp"

bool stop = false;
bool verbose = false;

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		std::cerr << "Usage: " << argv[0] << " [-v] IP_src MAC_src IP_target MAC_target" << std::endl;
		return 1;
	}

	std::string ip_src;
	std::string mac_src;
	std::string ip_target;
	std::string mac_target;

	if (argc == 6)
	{
		if (strcmp(argv[1], "-v") == 0)
			verbose = true;
		else
		{
			std::cerr << "Usage: " << argv[0] << " [-v] IP_src MAC_src IP_target MAC_target" << std::endl;
			return 1;
		}
		ip_src = argv[2];
		mac_src = argv[3];
		ip_target = argv[4];
		mac_target = argv[5];
	}
	else {
		ip_src = argv[1];
		mac_src = argv[2];
		ip_target = argv[3];
		mac_target = argv[4];
	}

	signal(SIGINT, signalHandler);
	
	const std::string ip_poisoner = "10.10.0.103";
	const std::string mac_poisoner = "00:00:00:00:00:03";

	//check if ips and mac addresses are valid by using regex expressions
	if (!regex_match(ip_src, regex("([0-9]{1,3}\\.){3}[0-9]{1,3}")))
	{
		cout << "Invalid IP address for IP-src" << endl;
		return (1);
	}
	if (!regex_match(mac_src, regex("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})")))
	{
		cout << "Invalid MAC address for MAC-src" << endl;
		return (1);
	}
	if (!regex_match(ip_target, regex("([0-9]{1,3}\\.){3}[0-9]{1,3}")))
	{
		cout << "Invalid IP address for IP-target" << endl;
		return (1);
	}
	if (!regex_match(mac_target, regex("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})")))
	{
		cout << "Invalid MAC address for MAC-target" << endl;
		return (1);
	}

	t_arping_args args;
	args.sender_ip = ip_src;
	args.receiver_ip = ip_target;
	args.sender_mac = mac_src;
	std::thread target_spoofer(arping, args);
	t_arping_args args2;
	args2.sender_ip = ip_target;
	args2.receiver_ip = ip_src;
	args2.sender_mac = mac_target;
	std::thread source_spoofer(arping, args2);
	
    std::thread packet_capturer(capture_and_forward, ip_src, mac_src, ip_target, mac_target);
	
	packet_capturer.join();
	source_spoofer.join();
	target_spoofer.join();

	return 0;
}

void signalHandler(int signum)
{
    cout << endl << ">>\tTermination signal received. Stopping packet capture . . .\t<<" << endl;
	stop = true;
	return ;
}