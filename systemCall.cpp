# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
int main()
{
	warmUp();
	uint64_t start,end,results[iterations];
	getStartTick(start);
	int pid = getpid();
	getEndTick(end);
	cout << end - start << "\n";
	return 0;
}
