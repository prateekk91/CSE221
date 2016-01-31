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
			else if (pid == -1)
			{
				cout << "Process creation failed";
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
//		cout << sum << endl;
		results[i] = sum;
//		cout << results[i] << endl;
	}
	writeToFile(results,"procCreateCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procCreateTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Proc create mean= " << meanAndVariance.first << "\n";
	cout << "Proc create variance= " << meanAndVariance.second << "\n";
	return 0;
}
