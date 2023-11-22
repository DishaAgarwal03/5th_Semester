%{ 
#include<stdio.h>
int words=0;
int chars=0;
int blanks=0;
int lines=0;
%}
%%
[a-zA-Z]+ { words++; chars += yyleng; }
" " {blanks++; chars++;}
\t {blanks=blanks+4; chars+=4;}
\n {lines++; chars++;}
. chars++;
%%
int yywrap() 
{ 
	return 1;
}
int main()
{
	printf("Enter input: ");
	yylex();
	printf("words: %d characters: %d blanks: %d lines: %d\n", words, chars, blanks, lines);
}