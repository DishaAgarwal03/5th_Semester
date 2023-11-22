// check
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int cur=0;
char str[100];

void S();
void U();
void V();
void W();

void invalid()
{
	printf("-----ERROR-----\n");
	exit(1);
}
void valid()
{
	printf("-----SUCCESS-----\n");
	exit(0);
}
void S()
{
	U();
	V();
	W();
}
void U()
{
	if(str[cur]=='(')
	{
		cur++;
		S();
		if(str[cur]==')')
		{
			cur++; return;
		}
		else 
			invalid();
	}
	else if(str[cur]=='a')
	{
		cur++;
		S();
		if(str[cur]=='b')
		{
			cur++; return;
		}
		else 
			invalid();
	}
	else if(str[cur]=='d')
	{
		cur++; return;
	}
	else
		invalid();
}
void V()
{
	if(str[cur]=='a')
	{
		cur++;
		V();
	}
	// don't write else statement since Aprime has epsilon in its production
	// else
	// 	invalid();
}
void W()
{
	if(str[cur]=='c')
	{
		cur++;
		W();
	}
	// don't write else statement since Aprime has epsilon in its production
	// else
	// 	invalid();
}
void main()
{
	printf("Enter string: ");
	scanf("%s",str);
	S();
	if(str[cur]=='$')
		valid();
	else
		invalid();
}