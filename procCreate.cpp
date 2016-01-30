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
	double results[iterations], sum;
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0;j<innerLoop;j++)
		{
			getStartTick(start);
			int pid = fork();
			if (pid == 0)
			{
				exit(0);
			}
			else
			{
				int returnStatus;
				waitpid(pid, &returnStatus, 0);
				getEndTick(end);
				sum += end - start;
			}
			
		}
		sum /= innerLoop;
		results[i] = sum;
		writeToFile(results,"procCreateResult.txt");
	}
	return 0;
}
