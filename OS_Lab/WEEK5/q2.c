//Demonstrate creation, writing to, and reading from a pipe

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  //for read, write, pipe

int main(int argc, char *args[])
{
	int n;
	int fd[2];
	char buf[1025];
	char *data="Hi, this is Disha Agarwal";
	pipe(fd);

	write(fd[1],data,strlen(data));
	if((n=read(fd[0], buf, 1024))>=0)
	{
		buf[n]=0;
		printf("Read %d bytes from the pipe: \"%s\" \n",n,buf);
	}
	else
		perror("Read");
	exit(0);
}