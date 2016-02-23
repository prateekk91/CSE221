# include <iostream>
# include <cstdio>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
# define bigSize 67108864
# define smallSize 4194304
int main()
{
	
	
	uint64_t start,end;
	char* big = new char[bigSize];
	char* small = new char[smallSize];
	double resultsRead[iterations];
	double resultsWrite[iterations];
	
	for(int i=0;i<bigSize;++i)
		big[i] = (char)(rand()%256);
		
	int count =bigSize/smallSize;
	char * src = big;
	for(int i=0;i<iterations;++i)
	{
		src = big;
		int k;
		getStartTick(start);
		#define ONE memcpy(small,src,smallSize);src += smallSize;
		#define TEN ONE ONE ONE ONE ONE ONE ONE ONE ONE ONE
		#define SIXTEEN TEN ONE ONE ONE ONE ONE ONE
		SIXTEEN
		getEndTick(end);
		resultsRead[i] = (end-start)/(count*smallSize * 1.0);
	}
	
	for (int i=0;i<iterations;i++)
	{
		src = big;
		int k;
		getStartTick(start);
		#define ONEW memcpy(src,small,smallSize);src += smallSize;
		#define FIVE ONEW ONEW ONEW ONEW ONEW
		#define SIXTEENW FIVE FIVE FIVE ONEW
		SIXTEENW
		getEndTick(end);
		resultsWrite[i] = (end-start)/(count*smallSize * 1.0);
	}
	
	delete[] big;
	delete[] small;
	writeToFile(resultsRead,"bandwidthReadCycles.txt");
	getTimeFromTicks(resultsRead);
	writeToFile(resultsRead,"bandWidthReadTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(resultsRead, iterations);
	cout << "Bandwidth read mean= " << meanAndVariance.first << "\n";
	cout << "Bandwidth read variance= " << meanAndVariance.second << "\n";


	writeToFile(resultsWrite,"bandwidthWriteCycles.txt");
	getTimeFromTicks(resultsRead);
	writeToFile(resultsWrite,"bandWidthWriteTime.txt");
	meanAndVariance = getMeanAndVariance(resultsWrite, iterations);
	cout << "Bandwidth write mean= " << meanAndVariance.first << "\n";
	cout << "Bandwidth write variance= " << meanAndVariance.second << "\n";

	return 0;
}
