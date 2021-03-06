#include<stdint.h>
#include<string>
#include<fstream>
# include<cstring>
# include <utility>
# include<algorithm>
using namespace std;
#define iterations 1000
# define innerLoop 100

void writeToFile(double *results,string fileName )
{
	ofstream myfile;
  	myfile.open (fileName.c_str());
  	
  	for(int i=0;i<iterations;++i)
  		myfile << results[i]<<endl;
  		
  	myfile.close();
}

void inline getStartTick(uint64_t &start)
{
	unsigned cycles_low, cycles_high;
	asm volatile ("CPUID\n\t"
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
}

void inline getEndTick(uint64_t &end)
{
	unsigned cycles_low, cycles_high;
	asm volatile("RDTSCP\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
		"%rbx", "%rcx", "%rdx");
	end = ( ((uint64_t)cycles_high << 32) | cycles_low );
}

void inline warmUp()
{
	uint64_t start,end;
	getStartTick(start);
	getEndTick(end);
	getStartTick(start);
	getEndTick(end);
	getStartTick(start);
	getEndTick(end);
}

pair<double, double> inline getMeanAndVariance(double *results, int iters)
{
	double sum = 0;
	double sigma = 0;
	sort(results, results+iters);
	cout << "Median value = " << results[iters/2] << endl;
	for (int i=10;i<iters-10;i++)
	{
		sum += results[i];
	}
	double mean = sum / (iters - 20);
	for (int i=10;i<iters-10;i++)
	{
		sigma += (mean - results[i]) * (mean - results[i]);
	}
	double variance = sigma / (iters-20);
	
	return make_pair(mean, variance);
}

void getTimeFromTicks(double *results)
{
	for (int i=0;i<iterations;i++)
	{
		results[i] = results[i] / 2.592711812;
	}
}

