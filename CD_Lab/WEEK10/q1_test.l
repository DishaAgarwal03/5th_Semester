%{
#include "q1_test.tab.h"
#include<stdio.h>
%}

%%
[0-9]+ {printf("NUM"); return NUM;}
\n {printf("NL"); return NL;}
";" {return SC;}
"char" {printf("TYPE"); return TYPE;}
[a-zA-Z_][a-zA-Z0-9_]* {printf("ID"); return ID;}
. {printf("%c",yytext[0]); return yytext[0];}
%%

int yywrap()
{
	return 1;
}