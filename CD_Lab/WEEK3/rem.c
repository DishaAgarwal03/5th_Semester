#include <stdio.h>
#include <stdlib.h>
#define 23
void main()
{
	FILE *fopen(),    *fp;
	int c ;
	fp = fopen("prog.c","r" ); 
	c = getc( fp ) ;
	while ( c!=EOF )
	{
	putchar( c );
	c = getc ( fp      );
	}
	fclose(	     fp);
}
