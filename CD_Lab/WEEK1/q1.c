#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f;
	int c=0,l=0;
	char ch,name[100];

	printf("Enter file name: ");
	scanf("%s",name);
	f=fopen(name,"r");
	if(f==NULL)
	{
		printf("Error\n");
		exit(0);
	}
	while(1)
	{
		ch=fgetc(f);
		if (ch==EOF)
			break;
		else if (ch=='\n')
			l++;
		else if (ch!=' ')
			c++;
	}
	printf("Number of characters and lines are %d and %d respectively\n",c,l+1);
	fclose(f);
}