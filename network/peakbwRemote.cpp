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
# define BYTES 1024*208
# define ONE_MB 1024*1024
# define FIVE_MB 5*ONE_MB
int main()
{
	warmUp();
	uint64_t start,end;
	double results[middleIters], sum;
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

	raddr.s_addr = inet_addr(ADDR_REMOTE);

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	remote_addr.sin_addr = raddr;
	
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
	
	for (int i=0;i<middleIters;i++)
	{
		sum = 0;
		for (int j=0;j<1;j++)
		{
			getStartTick(start);
			send(sock_fd, message.c_str(), BYTES, 0);
			getEndTick(end);
        		sum += end - start;
        	}
		sum /= 1;
		results[i] = sum;
        }
	close(sock_fd);
	writeToFile(results,"peakbwRemoteCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"peakbwRemoteTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, middleIters);
	cout << "Peak BW mean= " << meanAndVariance.first << "\n";
	cout << "Peak BW variance= " << meanAndVariance.second << "\n";
	cout << "Mean bandwidth= " << 1000000 * (208/meanAndVariance.first) << "\n";
	
	ofstream myfile;
	myfile.open ("peakBwRemoteResults.txt");
	myfile << "Peak Bw mean= " << meanAndVariance.first << "\n";
	myfile << "Peak Bw variance= " << meanAndVariance.second << "\n";
	myfile << "Mean bandwidth= " << 1000000 * (208/meanAndVariance.first) << "\n";
	myfile.close();
	
	return 0;
}
