//q4
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	char c;
	int in, out;
	in=open("infile.txt",O_RDONLY);
	out=open("outfile.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	if (in==-1 || out==-1)
		exit(0);
	while(read(in,&c,1)==1)
		write(out,&c,1);
}