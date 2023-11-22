#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define kwlen 21

typedef struct t{
	char name[200];
	int row;
	int column;
} TOKEN;


void getNextToken(FILE *fa, TOKEN t[])
{
	char kw[kwlen][100]={"if","else","break","case","char","const","continue","default","do","double","float",
						"for","int","return","short","sizeof","switch","typedef","void","while","main"};
	int i=-1,k,ll;
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

		//spaces
		else if(ca==' ')
			c++;

		//Tabs 
		else if(ca=='\t')
			c+=4;

		//EOL
		else if(ca=='\n')
		{
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

			// /,/=, //, /* */
			else if(ca=='/')
			{
				c++;
				ca=getc(fa);
				if(ca=='=')
				{
					t[i].name[k++]=ca;
					c++;
				}
				else if(ca=='/')
				{
					ca=getc(fa);
					while(ca!='\n')
						ca=getc(fa);
					i--;
					continue;
				}
				else if(ca=='*')
				{
					ca=getc(fa);
					while(1)
					{
						if (ca=='*')
						{
							if ((ca=getc(fa))=='/')
								break;
							if (ca=='*')
								continue;     //ADD THIS OTHERWISE DOES NOT WORK FOR ****/ -> even no. of * before /
						}
						if(ca=='\n')
						{
							c=1;
							r++;
						}
						ca=getc(fa);
					}
					c=1; i--;
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
					char word[100];
					word[0]=ca;
					ca=getc(fa);
					while(isalnum(ca) || ca=='_')
					{
						// t[i].name[k++]=ca;
						word[k++]=ca;
						c++;
						ca=getc(fa);
					}
					// t[i].name[k]='\0';
					word[k]='\0';
					for(ll=0;ll<kwlen;ll++)
					{
						if (strcmp(kw[ll],word)==0)
						{
							strcpy(t[i].name,word);
							break;
						}
					}
					if(ll==kwlen)
						strcpy(t[i].name,"id");
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
						ca=getc(fa);
						c++;
					}
					strcpy(t[i].name,"num");
					continue;
				}
			}
		}
		ca=getc(fa);
	}
	i++;
	strcpy(t[i].name,"EOF");
	t[i].row=r;
	t[i].column=c;
}
