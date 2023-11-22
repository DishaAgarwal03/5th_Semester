//consumer
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
	int open_mode = O_RDONLY;
	int buf[1];
	int bytes_read = 0;
	// memset(buffer, '\0', sizeof(buffer));
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	fd = open(fifoname, open_mode);
	printf("Process %d result %d\n", getpid(), fd);

	if (fd != -1) 
	{
		for(int i=0;i<4;i++)
		{
			res = read(fd, buf, bufsize);
			printf("%d ",buf[0]);
		}
		(void)close(fd);
	}
	else 
	{
		exit(EXIT_FAILURE);
	}
	printf("\nProcess %d finished, %d bytes read\n", getpid(), bytes_read);
	exit(EXIT_SUCCESS);
}