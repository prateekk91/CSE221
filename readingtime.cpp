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
	writeToFile(results,"readingTimeCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"readingTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Reading time mean= " << meanAndVariance.first << "\n";
	cout << "Reading time variance= " << meanAndVariance.second << "\n";
	return 0;
}
