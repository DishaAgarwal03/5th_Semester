#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa=fopen("rem.c","r");
	if (fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	fb=fopen("q1out.c","w");
	ca=getc(fa);
	while (ca!=EOF)
	{
		if (ca=='"')
		{
			do{
				putc(ca,fb);
				ca=getc(fa);
			}while(ca!='"');
			putc(ca,fb);
		}

		else if (ca==' ')
		{
			putc(ca,fb);
			while(ca==' ')
				ca=getc(fa);
			putc(ca,fb);
		}
		else if(ca=='\t')
			putc(' ',fb);
		else
			putc(ca,fb);
		ca=getc(fa);
	}
	printf("Modified!\n");
	fclose(fa);
	fclose(fb);
	return 0;
}