//arith: +,-,/,*,%           DONE
//shorthand: +=,-=,/=,%=,*=  DONE
//unary: ++,--               DONE
//rel: <,<=,>,>=,==,!=       DONE
//logical: !,&&,||           DONE
//assignment: =              DONE
//bitwise: &,|               DONE

//Special symbols            DONE
//keywords                   DONE
//numerical constants        DONE
//string literals            DONE
//identifiers				 DONE

//remove directives          DONE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct t{
	char name[200];
	int row;
	int column;
} TOKEN;

//comments not taken into account
void copytokens(TOKEN t[], int i)
{
	FILE *fb;
	fb=fopen("output.txt","w+");
	for(int j=0;j<i;j++)
	{
		if (t[j].name[0]=='\n')
			putc('\n',fb);
		else
			fprintf(fb," <%s,%d,%d> ",t[j].name,t[j].row,t[j].column);
	}

}

void getNextToken(FILE *fa, TOKEN t[])
{
	//char kw[20][100]={"if","else","break","case","char","const","continue","default","do","double","float",
	//					"for","int","return","short","sizeof","switch","typedef","void","while"};
	int i=-1,k;
	int r=1,c=1;
	char ca;
	ca=getc(fa);
	while (ca!=EOF)
	{
		//string literal
		if (ca=='"')
		{
			i++;
			t[i].row=r;
			t[i].column=c;
			k=0;
			do{
				t[i].name[k++]=ca;
				c++;
				ca=getc(fa);
			}while(ca!='"');
			t[i].name[k++]=ca;
			t[i].name[k]='\0';
		}

		//preprocessive directives
		else if (ca=='#')
		{
			while(ca!='\n')
				ca=getc(fa);
		}

		//Tabs and spaces
		else if(ca=='\t' || ca==' ')
			c++;

		//EOL
		else if(ca=='\n')
		{
			i++;
			t[i].name[0]='\n';
			c=1;
			r++;
		}

		else
		{
			k=0;
			i++;
			t[i].row=r;
			t[i].column=c;
			c++;
			t[i].name[k++]=ca;

			//=, ==
			if(ca=='=')
			{
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//!=,!
			else if(ca=='!')
			{
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//&&,&
			else if(ca=='&')
			{
				ca=getc(fa);
				if(ca=='&')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//||,|
			else if(ca=='|')
			{
				ca=getc(fa);
				if(ca=='|')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//<=,<
			else if(ca=='<')
			{
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//>=,>
			else if(ca=='>')
			{
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//+=,++,+
			else if(ca=='+')
			{
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else if(ca=='+')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//-=,--,-
			else if(ca=='-')
			{
				c++;
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else if(ca=='-')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			// /,/=
			else if(ca=='/')
			{
				c++;
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//*,*=
			else if(ca=='*')
			{
				c++;
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			//%,%=
			else if(ca=='%')
			{
				c++;
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else
				{
					continue;
				}
			}

			else 
			{
				//identifier/keyword
				if (isalpha(ca) || ca=='_')
				{
					ca=getc(fa);
					while(isalnum(ca) || ca=='_')
					{
						t[i].name[k++]=ca;
						c++;
						ca=getc(fa);
					}
					t[i].name[k]='\0';
					continue;
				}

				//Special symbol
				else if(ispunct(ca))
					t[i].name[k++]='\0';

				//Numerical constant
				else if(isdigit(ca))
				{
					ca=getc(fa);
					while(isdigit(ca) || ca=='.'){
						t[i].name[k++]=ca;
						ca=getc(fa);
						c++;
					}
					t[i].name[k]='\0';
					continue;
				}
			}
		}
		ca=getc(fa);
	}
	copytokens(t,i);
}

void main()
{
	FILE *fa,*fb;
	TOKEN t[200];
	fa=fopen("rem.c","r");
	if (fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}

	getNextToken(fa, t);

	//fb=fopen("q2out.c","w");
	printf("Modified!\n");
	fclose(fa);
	//fclose(fb);
}