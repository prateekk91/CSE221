#include<stdint.h>
#include<string>
#include<fstream>
# include<cstring>
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

