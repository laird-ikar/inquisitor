#include "../incs/arping.hpp"

extern bool stop;

void arping(
	const t_arping_args &args
	)
{
	while (1)
	{
		if (stop)
        {
			int pid_exit = fork();
			if (!pid_exit)
			{
				system(("arping -U -c 1 -S" + args.sender_ip + " -s " + args.sender_mac + " " + args.receiver_ip + " > /dev/null").c_str());
				break;
			}
            else
            {
                waitpid(pid_exit, NULL, 0);
                break;
            }
			break;
        }
			
		int pid = fork();
		if (!pid)
		{
			// std::cout << "alors les filles ca spoof ?" << std::endl;
			system(("arping -U -c 1 -S" + args.sender_ip + " " + args.receiver_ip + " > /dev/null").c_str());
            return;

		}
		else
		{
			waitpid(pid, NULL, 0);
		}
		sleep(1);
	}
	exit(0) ;
}