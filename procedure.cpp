#include<iostream>
using namespace std;
#include"getTicks.h"

void dummy()
{
}

void dummy(int a)
{
}

void dummy(int a,int b)
{
}
void dummy(int a,int b,int c)
{
}
void dummy(int a,int b,int c,int d)
{
}
void dummy(int a,int b,int c,int d,int e)
{
}
void dummy(int a,int b,int c,int d,int e,int f)
{
}
void dummy(int a,int b,int c,int d,int e,int f,int g)
{
}

int main()
{
	warmUp();
	uint64_t start,end;
	double results[iterations], sum = 0;
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy();
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure0Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure0Time.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 0 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 0 variance= " << meanAndVariance.second << "\n";
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure1Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure1Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 1 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 1 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure2Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure2Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 2 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 2 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2,3);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure3Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure3Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 3 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 3 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2,3,4);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure4Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure4Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 4 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 4 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2,3,4,5);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure5Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure5Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 5 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 5 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2,3,4,5,6);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure6Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure6Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 6 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 6 variance= " << meanAndVariance.second << "\n";
	
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0; j< innerLoop;j++)
		{
			getStartTick(start);
			dummy(1,2,3,4,5,6,7);
			getEndTick(end);
			sum += end - start;
		}
		results[i] = sum/innerLoop;
	}
	writeToFile(results,"procedure7Cycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"procedure7Time.txt");
	meanAndVariance = getMeanAndVariance(results, iterations);
	cout << "Procedure 7 mean= " << meanAndVariance.first << "\n";
	cout << "Procedure 7 variance= " << meanAndVariance.second << "\n";
	
	
	return 0;
}
