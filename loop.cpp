#include<iostream>
using namespace std;
#include"getTicks.h"


int main()
{
	warmUp();
	uint64_t start,end;
	double sum, results[iterations];
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0;j<innerLoop;j++)
		{
			getStartTick(start);
			for(int k=0;k<10;++k);
			getEndTick(end);
			sum += end - start;
		}
		sum /= innerLoop;
		results[i] = sum;
	}
	writeToFile(results,"loopCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"loopTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Loop mean= " << meanAndVariance.first << "\n";
	cout << "Loop variance= " << meanAndVariance.second << "\n";
	return 0;
}
