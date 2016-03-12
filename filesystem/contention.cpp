# include <iostream>
# include "getTicks.h"
# include <unistd.h>
# include <signal.h>
# include<stdlib.h>
# include <unistd.h>
# include<sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include<sys/wait.h>
# include <string>
#include <stdlib.h>
# define FOUR_KB 4096
# define ONE_MB 1048576
//Generate 9 files, starting from file1 to ... file9, starting with 32MB, doubling up the size each time
int main()
{
	warmUp();
	uint64_t start,end;
	char buffer[ONE_MB];
	string prefix = "";
	string files[] = {"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11","f12","f13","f14","f15","f16","f17","f18","f19","f20"};
	double results[iterations], sum;
	long long int fileSize = 32 * ONE_MB;
	for (int k=0;k<20;k++)
	{
		for(int l=0;l<=k;++l)
		{
		    pid = fork();
		    if(pid < 0) 
		    {
			printf("Error");
			exit(1);
		    }
		    else if (pid ==0)
		    {
			for(int i=0;i<iterations;++i)
			{
				sum = 0;
				for (int j=0;j<innerLoop;j++)
				{
					int fd = open((prefix + files[l]).c_str(), O_RDONLY | O_DIRECT);
					if (fd <= 0)
					{
						cout << "open failed\n";
					}
					int n;
					getStartTick(start);
					long long int tot = 0;
					while ( n=read(fd, &buffer, FOUR_KB) > 0)
					{
						if (n<0)
							cout << "Read error\n";
					}
					getEndTick(end);
					close (fd);
			 		sum += end - start;	
				}
				sum /= innerLoop;
				results[i] = sum;
			}
			string fileName = files[l] + std::string(k) +  "Cycles.txt";
			string fileTimeName = files[l] + std::string(k) +"Time.txt";
			writeToFile(results, fileName);
			getTimeFromTicks(results, lessIter);
			writeToFile(results, fileTimeName);
			pair<double, double> meanAndVariance = getMeanAndVariance(results, lessIter);
			cout << "File: " << files[k] << "\n";
			cout << "File read mean= " << meanAndVariance.first << "\n";
			cout << "File read variance= " << meanAndVariance.second << "\n";
			cout << "Average read time=" << (meanAndVariance.first * ONE_MB / fileSize) << "\n";
		
			ofstream myfile;
			fileName = files[k] + "FileCacheResults";
			myfile.open (fileName.c_str());
	  		myfile << "File: " << files[k] << "\n";
			myfile << "File read mean= " << meanAndVariance.first << "\n";
			myfile << "File read variance= " << meanAndVariance.second << "\n";
			myfile << "Average read time=" << (meanAndVariance.first * ONE_MB / fileSize) << "\n";
			myfile.close();
			
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	return 0;
}
