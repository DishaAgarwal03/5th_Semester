#include <stdio.h>
#include <stdlib.h>
#define 23
void main() //jedglwei'"
{
	FILE *fopen(),    *fp;/*jsg
	wkdhwkli
	akwjwe*/
	int c ;
	fp = fopen("prog.c","r" ); //olqwdkbj 
	c = getc( fp ) ;
	while ( c!=EOF )
	{
	putchar( c );
	c = getc ( fp      );
	}
	printf("Hello %d %d",2,3);
	fclose(	     fp);
}
