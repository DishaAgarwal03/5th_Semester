//producer
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define fifoname "/tmp/my_fifo"
#define bufsize 4

int main()
{
	int fd;
	int res;
	int open_mode = O_WRONLY;
	int bytes_sent = 0;
	char buffer[bufsize + 1];
	int arr[4];

	printf("Enter 4 numbers: ");
	for(int i=0;i<4;i++)
		scanf("%d",&arr[i]);

	if (access(fifoname, F_OK) == -1) 
	{
		res = mkfifo(fifoname, 0777);
		if (res != 0) 
		{
			fprintf(stderr, "Could not create fifo %s\n", fifoname);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	fd = open(fifoname, open_mode);
	// printf("Process %d result %d\n", getpid(), fd);
	if (fd != -1) 
	{
		for(int i=0;i<4;i++)
		{
			res = write(fd, &arr[i], bufsize);
			if (res == -1) 
			{
				fprintf(stderr, "Write error on pipe\n");
				exit(EXIT_FAILURE);
			}	
		}
		(void)close(fd);
	}
	else 
		exit(EXIT_FAILURE);
	
	printf("Process %d finished\n", getpid());
	exit(EXIT_SUCCESS);
}