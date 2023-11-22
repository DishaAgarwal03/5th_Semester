#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  //for read, write
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h>  //for wait.h
#include<fcntl.h>  //for modes like O_RDONLY
#include<limits.h>  //for PIPE_BUF

#define fifoname "/tmp/my_fifo"
#define bufsize PIPE_BUF

int main(int argc, char *args[])
{
	int fd;
	pid_t pid;
	char buf[bufsize];
	int n;
	int res=mkfifo(fifoname,0777);
	if (res==0)
			printf("FIFO created\n");

	pid=fork();

	if(pid==-1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(pid==0)
	{
		//child - reads
		fd = open(fifoname, O_RDONLY);
		while((n=read(fd,buf,bufsize))>0)  
		{
			write(STDOUT_FILENO, buf, n);
			// write(STDOUT_FILENO, " ", 1);  //not working
		}
		write(STDOUT_FILENO, "\n", 1);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		//parent - writes
		fd = open(fifoname, O_WRONLY);
		int k=1;
		while(k<argc)
		{
			strcat(args[k]," \0");
			write(fd, args[k], strlen(args[k]));
			k++;
		}
		close(fd); //reader will see EOF
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}