#include<iostream>
using namespace std;
#include"getTicks.h"
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>

uint64_t end;
void *temp(void* ptr)
{
	//measure end time in created pthread
	getEndTick(end);
}
int main()
{
	pthread_t thread1;
	uint64_t start;
	double sum, results[iterations];
	pthread_attr_t attr;	//attribute to be used for thread creation
	int policy = 0;
	int max_prio_for_policy = 0;
	struct sched_param param;

	pthread_attr_init(&attr);	//initialize the attr
	// don't inherit the parent thread scheduling policy, make it explicit
	int error = pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	if(error!=0)
	{
		cout<<"failed to set inherit sched\n";
	}
	// set attr policy to round robin
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	// get max priority for the new policy
	pthread_attr_getschedpolicy(&attr, &policy);
	max_prio_for_policy = sched_get_priority_max(policy);
	cout<<"max prio is "<<max_prio_for_policy<<endl;
	param.sched_priority = max_prio_for_policy;
	
	// set max priority in the attr
	error=pthread_attr_setschedparam(&attr,&param);
	if(error!=0)
	{
		cout<<"failed to set priority\n";
	}
	
	// increase my own, i.e. main thread priority
	pthread_t thId = pthread_self();
	param.sched_priority = max_prio_for_policy-5;
	error = pthread_setschedparam(thId,SCHED_RR, &param);
	if(error!=0)
	{
		cout<<"failed to set priority of main thread\n";
	}
	
	for(int i=0;i<iterations;++i)
	{
		sum = 0;
		for (int j=0;j<innerLoop;j++)
		{
			getStartTick(start);
			error = pthread_create (&thread1, &attr, temp, NULL);
			if(error)
			{
				cout<<"error cant create thread "<<error<<endl;
				return 1;
			}
		
			pthread_join( thread1, NULL);
			//end time measured in child thread
			sum += end - start;
			//getEndTick(end);
		}
		sum /= innerLoop;
		results[i] = sum;
	}
	//pthread_attr_destroy(&attr);
	writeToFile(results,"pthreadCycles.txt");
	getTimeFromTicks(results);
	writeToFile(results,"pthreadTime.txt");
	return 0;
}
