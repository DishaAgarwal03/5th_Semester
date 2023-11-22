//q1
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *args[])
{
	int fd, k=0, i=0;
	char line[200];
	char c;
	if ( argc!=3 || (fd=open(args[2],O_RDONLY))==-1 )
	{
		printf("Error");
		exit(0);
	}

	while(read(fd,&c,1)==1)
	{
		if (c!='\n')
		{
			line[i]=c;
			i++;
		}
		else
		{
			line[i]='\0';
			i=0;
			k++;
			if(strstr(line,args[1]))
				printf("Line: %d   %s\n",k,line);
		}
	}
}