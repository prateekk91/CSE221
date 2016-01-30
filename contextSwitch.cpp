# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>
int main()
{
	warmUp();
	uint64_t start,end;
	double results[iterations];
	int fd[2];
	char val;
	// create pipe descriptors
	pipe(fd);

			
	for(int i=0;i<100;++i)
	{
		double sum = 0;
		for (int j=0;j<innerLoop;j++)
		{
			// fork() returns 0 for child process, child-pid for parent process.
			if (fork() == 0)
			{
				write(fd[1], "a", 1);
				exit(0);
			}
			else
			{  
				getStartTick(start);
				read(fd[0], &val, 1);
				getEndTick(end);
				sum += end - start;
			}
		}
		sum /= innerLoop;
		results[i] = sum;
			
		writeToFile(results,"contextSwitchResults.txt");
	}
	return 0;
}
