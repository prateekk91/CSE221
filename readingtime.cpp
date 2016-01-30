#include<iostream>
#include"getTicks.h"
# include<unistd.h>
int main()
{
	uint64_t start,end;
	double sum, results[iterations];
	warmUp();
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0;j<innerLoop;j++)
		{
			getStartTick(start);
			getEndTick(end);
			sum += end - start;
		}
		sum /= innerLoop;
		results[i] = sum;
	}
	writeToFile(results,"readingTimeResults.txt");
	return 0;
}
