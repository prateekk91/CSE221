# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<stdlib.h>
# include <unistd.h>
# include<sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include<sys/wait.h>
# include <string>
#include <stdlib.h>
# define FOUR_KB 4096
# define ONE_MB 1048576
# define READLIMIT 4096000
int main ( int argc, char *argv[])
{
	warmUp();
	uint64_t start,end;
	static char buffer[FOUR_KB] __attribute__ ((__aligned__ (FOUR_KB)));
	double results[middleIters], sum;
	long long int fileSize = 31 * ONE_MB;
	for(int i=0;i<middleIters;++i)
	{
		sum = 0;
		for (int j=0;j<lessInner;j++)
		{
			int fd = open(argv[1], O_RDONLY | O_DIRECT);
			if (fd <= 0)
			{
				cout << "open failed\n";
			}
			int n;
			getStartTick(start);
			int tot = 0;
			while ( true )
			{
				n=read(fd, &buffer, FOUR_KB);
				if (n<0)
					cout << "Read error\n";
				tot += n;
				if (tot >= fileSize || n==0)
					break;
			}
//				cout << tot << "\n";
			getEndTick(end);
//				cout << "total:" << tot << " k: " << k << "\n";
			close (fd);
			sum += end - start;	
		}
		sum /= lessInner;
		results[i] = sum;
	}
	getTimeFromTicks(results, middleIters);
	pair<double, double> meanAndVariance = getMeanAndVariance(results, middleIters);
	cout << (int)(meanAndVariance.first * FOUR_KB / fileSize) << "\n";
	return 0;
}
