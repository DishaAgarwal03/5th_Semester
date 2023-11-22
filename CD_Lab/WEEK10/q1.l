%{
#include "q1.tab.h"
#include<stdio.h>
%}

%%
[0-9]+ {return NUM;}
\n {return NL;}
"char"|"int"|"float" {return TYPE;}
[";"|"["|"]"|","] {return yytext[0];}
[_a-zA-Z][a-zA-Z0-9_]* {return ID;}
%%

int yywrap()
{
	return 1;
}