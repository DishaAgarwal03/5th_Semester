#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2;
	char c,name[100];
	long pos;

	printf("Enter input file name: ");
	scanf("%s",name);
	f1=fopen(name,"r");
	if(f1==NULL)
	{
		printf("Error\n");
		exit(0);
	}

	printf("Enter output file name: ");
	scanf("%s",name);
	f2=fopen(name,"w+");

	fseek(f1,0,SEEK_END);
	pos=ftell(f1);       //ftell gives the current position which is the file size here
	fseek(f1,0,SEEK_SET);
	pos--;

	while(pos>=0)
	{
		fseek(f1,pos,SEEK_SET);
		c=fgetc(f1);
		putc(c,f2);
		pos--;
	}

}