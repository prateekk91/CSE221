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
# define ADDR "127.0.0.1"
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

	raddr.s_addr = inet_addr(ADDR);

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	remote_addr.sin_addr = raddr;
		
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
	for (int i=0;i<iterations;i++)
	{
		sum = 0;
		int tot = 0;
		for (int j=0;j<10;j++)
		{

			getStartTick(start);
			send(sock_fd, message.c_str(), BYTES, 0);
			bytes_read = recv(sock_fd, buffer, BYTES, 0);
			getEndTick(end);
//			tot += bytes_read;
//			cout << buffer << "\n";
			sum += end - start;
        	}
        	sum /= 10;
		results[i] = sum;
        }
	close(sock_fd);
	writeToFile(results,"rttLocalCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"rttTLocalime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Local Rtt mean= " << meanAndVariance.first << "\n";
	cout << "Local Rtt variance= " << meanAndVariance.second << "\n";
	
	ofstream myfile;
	myfile.open ("rttLocalResults.txt");
	myfile << "Local Rtt mean= " << meanAndVariance.first << "\n";
	myfile << "Local Rtt variance= " << meanAndVariance.second << "\n";
	myfile.close();
	
	return 0;
}
