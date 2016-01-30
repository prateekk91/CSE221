#include<iostream>
using namespace std;
#include"getTicks.h"

void dummy()
{
}

void dummy1(int a)
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
	uint64_t start,end,results[iterations];
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy();
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure0Results.txt");
	for(int j=0;j<iterations;++j)
	{
		getStartTick(start);
		dummy1(1);
		getEndTick(end);
		results[j] = end-start;
	}
	writeToFile(results,"procedure1Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure2Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2,3);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure3Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2,3,4);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure4Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2,3,4,5);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure5Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2,3,4,5,6);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure6Results.txt");
	for(int i=0;i<iterations;++i)
	{
		getStartTick(start);
		dummy(1,2,3,4,5,6,7);
		getEndTick(end);
		results[i] = end-start;
	}
	writeToFile(results,"procedure7Results.txt");
	return 0;
}
