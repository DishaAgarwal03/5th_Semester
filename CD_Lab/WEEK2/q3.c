#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
int main()
{
	FILE *fa;
	char ca;
	int i=0;
	char kw[20][100]={"IF","ELSE","BREAK","CASE","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","FLOAT",
						"FOR","INT","RETURN","SHORT","SIZEOF","SWITCH","TYPEDEF","VOID","WHILE"};
	char word[100];
	fa=fopen("rem.c","r");
	if (fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	ca=getc(fa);
	while (ca!=EOF)
	{   
		if (isalpha(ca))
		{
			word[i++]=toupper(ca);
		}
		
		else
		{
			word[i]='\0';
			i=0;
			for(int j=0;j<20;j++)
				if(strcmp(kw[j],word)==0)
				{
					printf("%s\n",word);
					break;
				}
		}

		ca=getc(fa);
	}
	fclose(fa);
	return 0;
}