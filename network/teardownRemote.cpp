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
# define BYTES 56
int main()
{
	warmUp();
	uint64_t start,end;
	double results[iterations], sum;
	int sock_fd, status, bytes_read;
	struct addrinfo remote;
	struct sockaddr_in remote_addr;
	struct in_addr raddr;
	char buffer[BYTES];
	string message = "";

	message.append(BYTES, '.');

	remote.ai_family = AF_INET;
	remote.ai_socktype = SOCK_STREAM;

	raddr.s_addr = inet_addr(ADDR_REMOTE);

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	remote_addr.sin_addr = raddr;
	
	for (int i=0;i<iterations;i++)
	{
		sum = 0;
		for (int j=0;j<10;j++)
		{
			if ((sock_fd = socket(remote.ai_family, remote.ai_socktype, remote.ai_protocol)) == -1) 
			{
				cout << "Can't open socket\n";
				exit(1);
			}	

			if (connect(sock_fd, (struct sockaddr *) &remote_addr, sizeof remote_addr) == -1) 
			{
				cout << "Can't connect\n";
				close(sock_fd);
				exit(1);
			}
			getStartTick(start);
			close(sock_fd);
			getEndTick(end);
        		
			sum += end - start;
        	}
		sum /= 10;
		results[i] = sum;
        }
	
	writeToFile(results,"teardownRemoteCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"teardownRemoteTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Teardown mean= " << meanAndVariance.first << "\n";
	cout << "Teardown variance= " << meanAndVariance.second << "\n";
	
	ofstream myfile;
	myfile.open ("tearDownRemoteResults.txt");
	myfile << "Teardown mean= " << meanAndVariance.first << "\n";
	myfile << "Teardown variance= " << meanAndVariance.second << "\n";
	myfile.close();
	return 0;
}
