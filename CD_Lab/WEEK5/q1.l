%{ 
#include<stdio.h>
int vowels=0;
int consonants=0;
%}
%%
[aeiouAEIOU] vowels++;
[a-zA-Z] consonants++;
%%
int yywrap() 
{ 
	return 1;
}
int main()
{
	printf("Enter input: ");
	yylex();
	printf("vowels: %d consonants: %d\n", vowels, consonants);
}