//q2
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *args[])
{
	int fd, k=0, i=0, p=0;
	char line[200];
	char c;
	for(int j=1;j<3;j++)
	{
		if ( argc!=3 || (fd=open(args[j],O_RDONLY))==-1 )
		{
			printf("Error");
			exit(0);
		}

		p=0;

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
				p++;
				printf("Line: %d   %s\n",p,line);

				if(k==20)
				{
					fgetc(stdin);    //for input from keyboard
					k=0;
				}
			}
		}
	}
}