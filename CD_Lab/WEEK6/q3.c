// check
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int cur=0;
char str[100];

void S();
void A();
void Aprime();
void B();

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
	if(str[cur]=='a')
	{
		cur++;
		A();
		if(str[cur]=='c')
		{
			cur++;
			B();
			if(str[cur]=='e')
			{ 
				cur++; return; 
			}
			else
				invalid();
		}
		else
			invalid();
	}
	else
		invalid();
}
void A()
{
	if(str[cur]=='b')
	{
		cur++;
		Aprime();
	}
	else
		invalid();
}
void Aprime()
{
	if(str[cur]=='b')
	{
		cur++;
		Aprime();
	}
	// don't write else statement since Aprime has epsilon in its production
	// else
	// 	invalid();
}
void B()
{
	if(str[cur]=='d')
	{
		cur++;
		return;
	}
	else
		invalid();
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