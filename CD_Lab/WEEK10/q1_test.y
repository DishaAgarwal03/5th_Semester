%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
%}

%token NUM ID NL TYPE SC 

%%
aug : decl NL { printf("Valid Expression\n"); exit(0);}
	;
decl : TYPE ' ' ID SC  
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