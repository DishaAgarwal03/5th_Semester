#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2,*fr;
	char c1=' ',c2=' ',name1[100],name2[100];

	printf("Enter file names: ");
	scanf("%s %s",name1,name2);
	f1=fopen(name1,"r");
	f2=fopen(name2,"r");
	if (f1==NULL || f2==NULL)
	{
		printf("Error");
		exit(0);
	}
	printf("Enter resultant file name: ");
	scanf("%s",name1);
	fr=fopen(name1,"w+");
	while(c1!=EOF || c2!=EOF)
	{
		while(c1!=EOF)
		{
			c1=fgetc(f1);			
			if(c1!=EOF)
				fputc(c1,fr);
			else
				fputc('\n',fr);   //if this file ends before and no line break put at the end
			if(c1=='\n')
				break;
		}

		while(c2!=EOF)
		{
			c2=fgetc(f2);
			if(c2!=EOF)
				fputc(c2,fr);
			else
				fputc('\n',fr);
			if(c2=='\n')
				break;
		}
	}

		fclose(f1); fclose(f2); fclose(fr);

}
