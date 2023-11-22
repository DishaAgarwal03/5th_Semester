%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
%}

%token NUM ID NL TYPE 

%%
decl : TYPE ID arr moreid ';' NL { printf("Valid Expression\n"); exit(0);}
	;
arr : '[' NUM ']'
	| 
	;
moreid : ',' ID arr
	|
	;
%%

int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	exit(0);
}
void main ()
{
	printf("Enter the expression:\n");
	yyparse();
}