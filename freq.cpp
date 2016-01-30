#include<iostream>
using namespace std;
#include"getTicks.h"
# include<unistd.h>

int main()
{
	warmUp();
	uint64_t start,end,results[iterations];
	getStartTick(start);
	sleep(10);
	getEndTick(end);
	cout << end - start << "\n";
	return 0;
}
