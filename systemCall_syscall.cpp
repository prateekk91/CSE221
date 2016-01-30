# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<sys/syscall.h>
int main()
{
	warmUp();
	warmUp();
	warmUp();
	warmUp();
	uint64_t start,end,results[iterations];
	
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		syscall(SYS_getpid);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"systemCallResults.txt");
	return 0;
}
