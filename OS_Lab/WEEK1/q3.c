//q3
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	int a=20;
	float b=10;
	char s[5]="Hello";
	printf("integer=%d  float=%f  string=%s  \ninteger to hexadecimal:%x\n",a,b,s,a);	
}