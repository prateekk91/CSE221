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
# define READLIMIT 409600
int main()
{
	warmUp();
	uint64_t start,end;
	static char buffer[FOUR_KB] __attribute__ ((__aligned__ (FOUR_KB)));
	string prefix = "/mnt/nfs/import/";
	string files[] = {"file1", "file2", "file3", "file4", "file5", "file6", "file7", "file8", "file9"};
	double results[lessIter], sum;
	for (int k=0;k<9;k++)
	{
		for(int i=0;i<lessIter;++i)
		{
			sum = 0;
			for (int j=0;j<lessInner;j++)
			{
				int fd = open((prefix + files[k]).c_str(), O_RDONLY | O_DIRECT);
				if (fd <= 0)
				{
					cout << "open failed\n";
				}
				int n;
				getStartTick(start);
				int tot = 0;
				while ( true )
				{
					n=read(fd, &buffer, FOUR_KB);
					if (n<0)
						cout << "Read error\n";
					tot += n;
					if (tot >= READLIMIT)
						break;
				}
				getEndTick(end);
//				cout << "total:" << tot << " k: " << k << "\n";
				close (fd);
				sum += end - start;	
			}
			sum /= lessInner;
			results[i] = sum;
		}
		string fileName = files[k] + "SequentialRemoteCycles.txt";
		string fileTimeName = files[k] + "SequentialRemoteTime.txt";
		writeToFile(results, fileName);
		getTimeFromTicks(results, lessIter);
		writeToFile(results, fileTimeName);
		pair<double, double> meanAndVariance = getMeanAndVariance(results, lessIter);
		cout << "File: " << files[k] << "\n";
		cout << "File read mean= " << (meanAndVariance.first * FOUR_KB / READLIMIT) << "\n";
		cout << "File read variance= " << (meanAndVariance.second * FOUR_KB / READLIMIT) << "\n";
		
		ofstream myfile;
		myfile.open ( (files[k] + "SequentialRemoteResults.txt").c_str());
  		myfile << "File: " << files[k] << "\n";
		myfile << "File read mean= " << (meanAndVariance.first * FOUR_KB / READLIMIT) << "\n";
		myfile << "File read variance= " << (meanAndVariance.second * FOUR_KB / READLIMIT) << "\n";
		myfile.close();
		
	}
	return 0;
}
