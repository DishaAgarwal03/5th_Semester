%{ 
#include<stdio.h>
int pint=0;
int nint=0;
int pfloat=0;
int nfloat=0;
%}
%%
-[1-9][0-9]* nint++;
"+"?[1-9][0-9]* pint++;
-[1-9][0-9]*"."[0-9]+ nfloat++;
"+"?[1-9][0-9]*"."[0-9]+ pfloat++;
%%
int main()
{
	char stat[100];
	/* need to write + in quotes since + also means more than 0 occurence*/
	printf("Enter input: ");
	scanf("%[^\n]s",stat);
	yy_scan_buffer(stat,sizeof(stat));
	yylex();
	printf("Positive integer: %d \nNegative integer: %d \nPositive floating point number: %d \nNegative floating point number: %d\n", pint, nint, pfloat, nfloat);
}

int yywrap() 
{ 
	return 1;
}