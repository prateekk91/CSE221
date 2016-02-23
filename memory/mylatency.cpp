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
#define MEGABYTE 1048576
#define KILOBYTE 1024
#define ALLOC_SIZE MEGABYTE/1024
#define REPEAT_COUNT 1
#define ARRAYS_COUNT 13
#define NUM_OF_STRIDES 4

void memory_latency(unsigned long size, unsigned long iters, unsigned long stride_size, FILE* file) 
{
	uint64_t start,end;
	long unsigned time_taken, ul, k;
	register long unsigned it = iters/100;
	int* p = NULL;
	int* array = (int*) malloc(sizeof(int) * size);
	for (k = 0; k < size; k+=stride_size) 
	{
		array[k] = rand()%100;	
	}
	p = array;
			
	long unsigned count = size / (stride_size * 100) + 1;
	int i;
	getStartTick(start);
	for (ul=0; ul < it; ul++) 
	{
		p = array;
		int mod = 0;
		for (k = 0; k < count; k++) 
		{	
			#define ONE i = *(p+mod);mod = (mod+stride_size)%size;
			#define TEN ONE ONE ONE ONE ONE ONE ONE ONE ONE ONE
			#define HUNDRED TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN
			HUNDRED;
		}
	}
	getEndTick(end);
	free(array);

	time_taken = (end - start) / (iters*count); //The time taken is the time spent on a single read.
	
	//Collect data
	unsigned long size_kB = (size * sizeof(char*)) / KILOBYTE;
	if (file != NULL) {
	    fprintf(file,"%lu %lu %lu\n", size_kB, stride_size, time_taken);
	    printf("%lukB %lu %luns %lu %lu\n", size_kB, stride_size, time_taken, iters, count);
	}
}

int main()
{
	warmUp();
	unsigned long iters = 1000000; // 2 Million iters.
	unsigned long array_sizes[ARRAYS_COUNT];// Array size will be 2^(8+array_size);
	unsigned long stride_sizes[NUM_OF_STRIDES];
	unsigned long i,j;
	stride_sizes[0] = 16; // Even with the smallest stride size, we explore the entire array for every array.
	stride_sizes[1] = 64;
	stride_sizes[2] = 256;
	stride_sizes[3] = 1024;
	array_sizes[0] = KILOBYTE;
	for (i = 1; i < ARRAYS_COUNT; i++) {
	    array_sizes[i] = array_sizes[i-1] << 1;
	}
	
	FILE *file;
	file = fopen("latency.txt","w+");	
	for(j = 0; j < NUM_OF_STRIDES; j++) {
		for (i = 0; i < ARRAYS_COUNT; i++) {
			memory_latency(
				array_sizes[i],
				iters,
				stride_sizes[j],
				file
			);
		}
	}
	
	fclose(file);
	return 0;
}
