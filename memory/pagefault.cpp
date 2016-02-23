#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <iostream>
# include "getTicks.h"
# define MB 1069056*5
#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	uint64_t start,end;
	double resultsRead[iterations];
	char *addr;
	int fd;
	struct stat sb;
	off_t offset, pa_offset;
	size_t length;
	ssize_t s;
	char *buffer;
	
	fd = open("file", O_RDONLY | O_DIRECT | O_SYNC);
	struct stat stats;
	  fstat(fd, &stats);
	  posix_fadvise(fd, 0, stats.st_size, POSIX_FADV_DONTNEED);

	if (fstat(fd, &stats) == -1)           /* To obtain file size */
	handle_error("fstat");
  

	offset = 0;
	pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	/* offset for mmap() must be page aligned */

	length = sb.st_size - offset;
	
	if (addr == MAP_FAILED)
		handle_error("mmap");
	for (int i=0; i<iterations;i++)
	{
		addr = (char *) mmap(NULL, stats.st_size, PROT_READ,
		       MAP_FILE|MAP_SHARED, fd, pa_offset);
		getStartTick(start);
		for (int j=0;j<stats.st_size;)
		{
			char a = addr[j];
			j += 40960;
		}
		getEndTick(end);
		resultsRead[i] = ((end - start) / (stats.st_size * 1.0)) * 40960;
		munmap(addr, stats.st_size);
	}
	
	writeToFile(resultsRead,"pageFaultCycles.txt");
	getTimeFromTicks(resultsRead);
	writeToFile(resultsRead,"pageFaultTime.txt");
	pair<double, double> meanAndVariance = getMeanAndVariance(resultsRead, iterations);
	cout << "Page Fault mean= " << meanAndVariance.first << "\n";
	cout << "Page Fault variance= " << meanAndVariance.second << "\n";
	
	return 0;
}

