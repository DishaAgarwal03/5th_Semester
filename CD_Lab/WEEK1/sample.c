#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2;
	char name[100], c;

	printf("Enter file name to read from ");
	scanf("%s",name);
	f1=fopen(name,"r");
	if (f1==NULL)
	{
		printf("Error");
		exit(0);
	}

	printf("Enter name of destination file ");
	scanf("%s",name);
	f2=fopen(name,"w+");

	c=fgetc(f1);
	while(c!=EOF)
	{
		fputc(c,f2);
		c=fgetc(f1);
	}
	printf("Contents successfully copied\n");
	fclose(f1);
	fclose(f2);

}