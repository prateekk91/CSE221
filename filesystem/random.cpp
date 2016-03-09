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
	long long int fileSize = 32*1024*1024;
	double results[lessIter], sum;
	for (int k=0;k<9;k++)
	{
		long long int total_blocks = fileSize / FOUR_KB;
			
		for(int i=0;i<lessIter;++i)
		{
			sum = 0;
				
			for (int j=0;j<lessInner;j++)
			{
				int fd = open((prefix+files[k]).c_str(), O_DIRECT);
				int n;
				getStartTick(start);
				srand(start);
				int tot = 0;
				while ( true )
				{
					off64_t offset = (off64_t) total_blocks * rand() / RAND_MAX;
//					cout << offset << "\n";
					off64_t err = lseek64(fd, offset * FOUR_KB, SEEK_SET);
					if (err <0 )
						cout<< "seek unsucessful  " << err <<"\n";
					n=read(fd, &buffer, FOUR_KB);
					if (n <0 )
						cout<< "read unsucessful\n";
					tot += n;
//					cout << tot << "\n";
					if (tot >= READLIMIT)
						break;
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
		
		ofstream myfile;
		myfile.open ("randomResults.txt");
  		myfile << "File: " << files[k] << "\n";
		myfile << "File read mean= " << meanAndVariance.first << "\n";
		myfile << "File read variance= " << meanAndVariance.second << "\n";
		myfile << "File read speed in MBPS = " << (READLIMIT*1000000000L * 1.0/(1024*1024))/meanAndVariance.first;
		fileSize *= 2;
		myfile.close();
		
	}
	return 0;
}
