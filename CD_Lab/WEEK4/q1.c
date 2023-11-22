// in week 3 ques
// changed variable names to id
// tab counted as 4 column?
// removed single line and multiline comments


// index, lexeme name, return type(if function), data type(if variable), token type, no. of arguments(if funct)
// no duplicates in the symbol table
// add in the o/p file: id1, id2,... instead of id,id,...

// array of structures OR
// linked list and hashing

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define kwlen 21
#define hashkey 32

typedef struct t{
	char name[200];
	char origname[200];  //added this for hashing
	int row;
	int column;
} TOKEN;

typedef struct node* NODE;
typedef struct node{
	int index;        	
	char lname[200];  	
	char returnt[200]; 	 
	char datat[200];  	 
	char tokent[200]; 	
	int numarg; 	 //number of arguments in the first appearance of the function 	
	NODE next;
} node;

int top=1;
char kw[kwlen][100]={"FILE","if","else","break","case","char","const","continue","default","do","double","float",
					 "for","int","return","short","sizeof","switch","typedef","void","while"};

NODE hash[hashkey]; // hashing scheme: (first character of token origname) %32 

NODE createnode(TOKEN t[], int i)  //return new NODE with appropriate info
{
	NODE temp=(NODE)malloc(sizeof(node));

	temp->next=NULL;
	temp->index=top;
	top++;

	strcpy(temp->lname,t[i].origname);

	TOKEN prevtoken = t[i-1];
	int j;
	for(j=0;j<kwlen;j++)
	{
		if(strcmp(prevtoken.name, kw[j])==0)
			break;
	}
	if(j==kwlen)
		// strcpy(prevtoken.name,"");
		prevtoken.name[0]='\0';

	TOKEN nexttoken = t[i+1];
	if(strcmp(nexttoken.name,"(")==0) //if '(' occurs after identifier name then it is a function
	{
		int count=0;
		strcpy(temp->tokent, "func");

		temp->datat[0]='\0';
		strcpy(temp->returnt, prevtoken.name);

		i++;  //i at '(' now
		if(t[i+1].name[0]!=')') //>=1 argument(s)
		{
			count++;
			while(strcmp(nexttoken.name,")")!=0)
			{
				i++;
				nexttoken=t[i];
				if(strcmp(nexttoken.name,",")==0)
					count++;
			}
		}
		temp->numarg=count;

	}
	else  //else it is a variable
	{
		strcpy(temp->tokent, "var");
		strcpy(temp->datat, prevtoken.name);  //therefore declaraion needs to be done before usage of any variable
		temp->returnt[0]='\0';
		temp->numarg=-1;
	}
}

int addhash(NODE temp, TOKEN t[], int i)  //return new id index
{
	int key=(t[i].origname[0])%hashkey;
	NODE cur=hash[key];
	if(cur==NULL)
	{
		hash[key]=temp;
		return temp->index;
	}
	while(cur->next)
		cur=cur->next;
	cur->next=temp;
	return temp->index;
}

int searchhash(TOKEN t[], int i)  //return -1 if not found else the id index
{
	int key=(t[i].origname[0])%hashkey;
	NODE cur=hash[key];
	while(cur)
	{
		if (strcmp(cur->lname , t[i].origname)==0)
			return cur->index;
		cur=cur->next;
	}
	return -1;
}

void displayhash()
{
	printf(" Index | Lexeme name | Return type |   Data type |  Token type | Number of args\n\n");
	for(int i=0;i<hashkey;i++)
	{
		NODE c=hash[i];
		while(c)
		{
			printf("%6d |%12s |%12s |%12s |%12s |%15d\n",c->index,c->lname,c->returnt,c->datat,c->tokent,c->numarg);
			c=c->next;
		}
	}
}

void addhashfile(NODE c)
{
	FILE *fc;
	fc=fopen("symboltable.txt","a");
	fprintf(fc,"|%6d |%12s |%12s |%12s |%12s |%15d|\n",c->index,c->lname,c->returnt,c->datat,c->tokent,c->numarg);
	fclose(fc);
}

void copytokens(TOKEN t[], int i)
{
	FILE *fb;
	int j=0;
	fb=fopen("output.txt","w+");
	char str[5];
	while(j<i)
	{
		if (t[j].name[0]=='\n')
		{
			putc('\n',fb);
			while(t[j].name[0]=='\n')  //skipping if more than one new line together
				j++;
		}
		else
		{
			if(strcmp(t[j].name,"id")==0)
			{
				int sear=searchhash(t,j);
				if (sear==-1)  //if not added then add it and return new id index:
				{
					NODE temp=createnode(t,j);
					//after temp node with all the info is created, add it to the hashmap and hashmap file
					sear=addhash(temp,t,j);
					addhashfile(temp);
				}
				// strcat(t[j].name,str(sear));  some error with str(sear)
				sprintf(str,"%d",sear);
				strcat(t[j].name,str);
			}
			fprintf(fb," <%s,%d,%d> ",t[j].name,t[j].row,t[j].column);
			j++;
		}
	}
	fclose(fb);
}

void getNextToken(FILE *fa, TOKEN t[])
{
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
						}
						if(ca=='\n')
						{
							t[i].name[0]='\n';
							c=1;
							r++;
							i++;
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
					{
						strcpy(t[i].name,"id");
						strcpy(t[i].origname,word);  //added this part for hashing
					}
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
	FILE *fa,*fc;
	TOKEN t[200];
	fa=fopen("rem.c","r");
	fc=fopen("symboltable.txt","w");
	if (fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}

	for(int i=0;i<hashkey;i++)
	{
		hash[i]=(NODE)malloc(sizeof(node));
		hash[i]=NULL;
	}
	fprintf(fc,"| Index | Lexeme name | Return type |   Data type |  Token type | Number of args|\n");
	fprintf(fc,"|_______|_____________|_____________|_____________|_____________|_______________|\n");
	fclose(fc);
	getNextToken(fa, t);
	displayhash();
	fclose(fa);
}