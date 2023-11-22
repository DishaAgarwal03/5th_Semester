/ This is a single line comment
/* *****This is a
******Multiline Comment
**** */
#include <stdio.h>
#include <stdlib.h>
#define 23
void main()
{
	FILE *fopen(),    *fp;
	int c ;
	fp = fopen("prog     .  c","r" ); //Comment
	c = getc( fp ) ;
	while ( c!=EOF )
	{
	putchar( c );
	c = getc ( fp      );
	}
	/*multiline
	comment */
	fclose(	     fp);
}