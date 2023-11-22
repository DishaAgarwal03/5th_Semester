%{ 
#include<stdio.h>
%}
%%
[a-zA-Z_][a-zA-Z0-9_]* printf(" Identifier");
%%
int yywrap() 
{ 
	return 1;
}
int main()
{
	printf("Enter the valid C statement");
	yylex();
	/* 	; scanf("%s",stat)
	; doesn't do anything with first input. why?
	*/
}
