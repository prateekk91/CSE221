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
	string files[] = {"file1", "file2", "file3", "file4", "file5", "file6", "file7", "file8", "file9", "file10"};
	double results[lessIter], sum;
	long long int fileSize = 32 * ONE_MB;
	for (int k=0;k<10;k++)
	{
		for(int i=0;i<lessIter;++i)
		{
			sum = 0;
			for (int j=0;j<lessInner;j++)
			{
				int fd = open((prefix + files[k]).c_str(), O_RDONLY);
				if (fd <= 0)
				{
					cout << "open failed\n";
				}
				int n;
				getStartTick(start);
				long long int tot = 0;
				while ( n=read(fd, &buffer, ONE_MB) > 0)
				{
					if (n<0)
						cout << "Read error\n";
				}
				getEndTick(end);
				close (fd);
				sum += end - start;	
			}
			sum /= lessInner;
			results[i] = sum;
		}
		string fileName = files[k] + "Cycles.txt";
		string fileTimeName = files[k] + "Time.txt";
		writeToFile(results, fileName);
		getTimeFromTicks(results, lessIter);
		writeToFile(results, fileTimeName);
		pair<double, double> meanAndVariance = getMeanAndVariance(results, lessIter);
		cout << "File: " << files[k] << "\n";
		cout << "File read mean= " << meanAndVariance.first << "\n";
		cout << "File read variance= " << meanAndVariance.second << "\n";
		cout << "Average read time=" << 1000000000 / (meanAndVariance.first * ONE_MB / fileSize) << "\n";
		
		ofstream myfile;
		fileName = files[k] + "FileCacheResults";
		myfile.open (fileName.c_str());
  		myfile << "File: " << files[k] << "\n";
		myfile << "File read mean= " << meanAndVariance.first << "\n";
		myfile << "File read variance= " << meanAndVariance.second << "\n";
		myfile << "Average read time=" << 1000000000 / (meanAndVariance.first * ONE_MB / fileSize) << "\n";
		myfile.close();
		fileSize *= 2;
		
	}
	return 0;
}
