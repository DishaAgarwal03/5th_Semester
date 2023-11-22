//sample - identify relational and assignment operators
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char c,buf[10];
	FILE *fp=fopen("digit.c","r");
	
	if(fp==NULL)
	{
		printf("Cannot optn\n");
		exit(0);
	}

	c=fgetc(fp);
	while(c!=EOF)
	{
		int i=0;
		buf[0]='\0';
		if (c=='=')
		{
			buf[i++]=c;
			c=fgetc(fp);
			if(c=='=')
			{
				buf[i++]=c;
				buf[i]='\0';
				printf("\nRelational operator: %s ",buf);
			}
			else
			{
				buf[i]='\0';
				printf("\nAssignment operator: %s ",buf);
			}
		}
		else
		{
			if (c=='<'||c=='>'||c=='!')
			{
				buf[i++]=c;
				c=fgetc(fp);
				if(c=='=')
					buf[i++]=c;
				buf[i]='\0';
				printf("\nRelational operator: %s ",buf);
			}
			else
			{
				buf[i]='\0';
			}
		}
		c=fgetc(fp);
	}
}