# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
# define PORT 7000
# define ADDR "192.168.0.103"
# define BYTES 56
# define ONE_MB 1024*1024
# define FIVE_MB 5*ONE_MB
int main()
{
	warmUp();
	uint64_t start,end;
	double results[iterations], sum;
	int sock_fd, status, bytes_read;
	struct addrinfo remote;
	struct sockaddr_in remote_addr;
	struct in_addr raddr;
//	char buffer[ONE_MB];
	string message = "";
	int buff_size = ONE_MB;
	message.append(FIVE_MB, '.');

	remote.ai_family = AF_INET;
	remote.ai_socktype = SOCK_STREAM;

	raddr.s_addr = inet_addr(ADDR);

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	remote_addr.sin_addr = raddr;
	
	for (int i=0;i<iterations;i++)
	{
		sum = 0;
		for (int j=0;j<10;j++)
		{
			getStartTick(start);
			if ((sock_fd = socket(remote.ai_family, remote.ai_socktype, remote.ai_protocol)) == -1) 
			{
				cout << "Can't open socket\n";
				exit(1);
			}	
			setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &buff_size, (int)sizeof(buff_size));
			if (connect(sock_fd, (struct sockaddr *) &remote_addr, sizeof remote_addr) == -1) 
			{
				cout << "Can't connect\n";
				close(sock_fd);
				exit(1);
			}
			int n = send(sock_fd, message.c_str(), FIVE_MB, 0);
//			cout <<" " << n << "\n";
			close(sock_fd);
			getEndTick(end);
        		
			sum += end - start;
        	}
		sum /= 10;
		results[i] = sum;
        }
	
	writeToFile(results,"peakbwCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"peakbwTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Peak BW mean= " << meanAndVariance.first << "\n";
	cout << "Peak BW variance= " << meanAndVariance.second << "\n";
	
	return 0;
}
