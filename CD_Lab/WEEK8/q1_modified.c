//FOR EXPECTED CHARACTERS, USE THE FOLLOW SETS
//WRITE FOLLOW SETS FOR RELOP, ADDOP, MULOP
//CHECK THE FIRST AND FOLLOW SETS

#include<stdlib.h>
#include<string.h>
#include "LA.c"
int cur=0;
TOKEN t[200];

void prog();
void decl();
void dtype();
void idlist();
void A();
void B();
void stlist();
void st();
void assign();
void expn();
void eprime();
void simplee();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void invalid(TOKEN ti, char *expected)   // cannot write expected[200]
{
	printf("-----ERROR-----\n");
	printf("Expected %s \nGot %s  Row: %d  Column: %d\n",expected,ti.name,ti.row,ti.column);
	exit(1);
}
void valid()
{
	printf("-----SUCCESS-----\n");
	exit(0);
}
void prog()
{
	if(strcmp(t[cur].name,"main")==0)
	{
		cur++;
		if(strcmp(t[cur].name,"(")==0)
		{
			cur++;
			if(strcmp(t[cur].name,")")==0)
			{ 
				cur++; 
				if(strcmp(t[cur].name,"{")==0)
				{
					cur++;
					decl();
					stlist();
					if(strcmp(t[cur].name,"}")==0)
					{
						cur++; return;
					}
					else invalid(t[cur],"} or id");
				}
				else invalid(t[cur],"{");
			}
			else invalid(t[cur],")");
		}
		else invalid(t[cur],"(");
	}
	else invalid(t[cur],"main");
}
void decl()
{
	if(strcmp(t[cur].name,"int")==0 || strcmp(t[cur].name,"char")==0)   // find the correct way to handle epsilon of decl
	{
		dtype();
		idlist();
		if(strcmp(t[cur].name,";")==0)
		{
			cur++;
			decl();
		}
		else invalid(t[cur],";");
	}
}
void dtype()
{
	if(strcmp(t[cur].name,"int")==0 || strcmp(t[cur].name,"char")==0)
	{
		cur++;
		return;
	}
	else invalid(t[cur],"int or char");
}
void idlist()
{
	if(strcmp(t[cur].name,"id")==0)
	{
		cur++;
		A();
	}
	else invalid(t[cur],"id");
}
void A()
{
	if(strcmp(t[cur].name,",")==0)
	{
		cur++;
		idlist();
	}
	else if(strcmp(t[cur].name,"[")==0)
	{
		cur++;
		if(strcmp(t[cur].name,"num")==0)
		{
			cur++;
			if(strcmp(t[cur].name,"]")==0)
			{
				cur++; B();
			}
			else invalid(t[cur],"]");
		}
		else invalid(t[cur],"num");
	}
}
void B()
{
	if(strcmp(t[cur].name,",")==0)
	{
		cur++;
		idlist();
	}
}
void stlist()
{
	if(strcmp(t[cur].name,"id")==0)
	{
		st();
		stlist();
	}
}
void st()
{
	assign();
	if(strcmp(t[cur].name,";")==0)
	{
		cur++; return;
	}
	else
		invalid(t[cur],"; * / % + - == != <= >= < >");
}
void assign()
{
	if(strcmp(t[cur].name,"id")==0)
	{
		cur++;
		if(strcmp(t[cur].name,"=")==0)
		{
			cur++;
			expn();
		}
		else invalid(t[cur],"=");
	}
	else invalid(t[cur],"id");
}
void expn()
{
	simplee();
	eprime();
}
void eprime()
{
	char tt[200];
	strcpy(tt,t[cur].name);
	if(strcmp(tt,"==")==0 || strcmp(tt,"!=")==0 || strcmp(tt,"<=")==0 || strcmp(tt,">=")==0 || strcmp(tt,">")==0 || strcmp(tt,"<")==0)
	{
		relop();
		simplee();
	}
}
void simplee()
{
	term();
	seprime();
}
void seprime()
{
	if(strcmp(t[cur].name,"+")==0 || strcmp(t[cur].name,"-")==0)
	{
		addop();
		term();
		seprime();
	}
}
void term()
{
	factor();
	tprime();
}
void tprime()
{
	if(strcmp(t[cur].name,"*")==0 || strcmp(t[cur].name,"/")==0 || strcmp(t[cur].name,"%")==0)
	{
		mulop();
		factor();
		tprime();
	}
}
void factor()
{
	if(strcmp(t[cur].name,"id")==0 || strcmp(t[cur].name,"num")==0)
	{
		cur++; return;
	}
	else invalid(t[cur],"id or num");
}
void relop()
{
	char tt[200];
	strcpy(tt,t[cur].name);
	if(strcmp(tt,"==")==0 || strcmp(tt,"!=")==0 || strcmp(tt,"<=")==0 || strcmp(tt,">=")==0 || strcmp(tt,">")==0 || strcmp(tt,"<")==0)
	{
		cur++; return;
	}
	else invalid(t[cur],"== or != or <= or >= or < or >");
}
void addop()
{
	if(strcmp(t[cur].name,"+")==0 || strcmp(t[cur].name,"-")==0)
	{
		cur++; return;
	}
	else invalid(t[cur],"+ or -");
}
void mulop()
{
	if(strcmp(t[cur].name,"*")==0 || strcmp(t[cur].name,"/")==0 || strcmp(t[cur].name,"%")==0)
	{
		cur++; return;
	}
	else invalid(t[cur],"* or / or %");
}
void main(int argc, char *args[])
{
	FILE *fa;
	fa=fopen(args[1],"r");
	if (fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	getNextToken(fa, t);
	printf("Tokens generated!\n");
	// for(int j=0;j<13;j++)
	// 	printf("%s\n",t[j].name);
	fclose(fa);

	prog();
	if(strcmp(t[cur].name,"EOF")==0)
		valid();
	else
		invalid(t[cur],"EOF");
}
