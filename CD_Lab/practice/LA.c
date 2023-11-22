// remove single line and multiline comments              DONE
// replace multiple blank spaces and tabs by single space DONE
// discard preprocessor directives                        DONE

// EXTRAS:
// recognize all keywords and replace by uppercase
// display function names + return type + number of arguments

// LA:
// arithmetic(+,-,/,%,*), logical(&&,||,!), bitwise (&,|),  DONE
// assignment(=) and relational(==,<,>,<=,>=,!=) operators  DONE
// special symbols                                          DONE
// keywords                                                 DONE
// numerical constants                                      DONE
// string literals                                          DONE
// identifiers                                              DONE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define kwlen 5

FILE *f;
int line = 1;
char keywords[kwlen][100]={"int","char","float","void","return"};
char token[100];

void goleft()
{
    fseek(f,-1,SEEK_CUR);
}

int cmp(char one[], char two[])
{
    if (strcmp(one,two)==0)
        return 1;
    return 0;
}

int iskeyword(char word[])
{
    for(int j=0;j<kwlen;j++)
        if(cmp(keywords[j],word))
            return 1;
    return 0;
}

void getNextToken()
{
    char c;
    memset(token, '\0', sizeof(token));
    int i=0;
    while(1)
    {
        c = fgetc(f);
        if(c==EOF)  // end of file
        {
            strcpy(token,"EOF");
            return;
        }
        else if(c=='"')  // string literal
        {
            do
            {
                token[i++]=c;
                c=fgetc(f);
            }while(c!='"');
            token[i]=c;
            return;
        }
        else if(c=='#')  // directives
        {
            while((c=fgetc(f))!='\n');  
            line++;
            continue;
        }
        else if(c=='\t' || c==' ')  // ignore spaces and tabs
            continue;  

        else if(c=='/')
        {
            c=fgetc(f);
            if(c=='/')  // single line comment
            {
                while((c=fgetc(f))!='\n');
                line++;
                continue;
            }
            else if(c=='*')  // multiline comment
            {
                c= ' ';
                do
                {
                    while(c!='*')
                    {     
                        c=fgetc(f);
                        if(c=='\n')
                            line++;
                    }
                    c=fgetc(f);
                    if(c=='\n')
                        line++;
                }while(c!='/');
                continue;
            }
            else // arithmetic : /
            {
                goleft();
                strcpy(token,"/");
                return;
            }
        }
        else if(c=='\n')
        {
            line++;
            continue;
        }

        // arithemetic : %,*,+,-
        else if(c=='+'|| c=='-' || c=='*' || c=='%')
        {
            token[0]=c;
            return;
        }

        // logical, bitwise and !=
        else if(c=='&')
        {
            token[0]=c;
            c=fgetc(f);
            if(c=='&')
                token[1]=c;
            else
                goleft();
            return;
        }
        else if(c=='|')
        {
            token[0]=c;
            c=fgetc(f);
            if(c=='|')
                token[1]=c;
            else
                goleft();
            return;
        }
        else if(c=='!')
        {
            token[0]=c;
            c=fgetc(f);
            if(c=='=')
                token[1]=c;
            else
                goleft();
            return;
        }

        // <,<=,>,>=,=,==
        else if(c=='<' || c=='>' || c=='=')
        {
            token[0]=c;
            c=fgetc(f);
            if(c=='=')
                token[1]=c;
            else
                goleft();
            return;
        }

        else if(isdigit(c))
        {
            while(isdigit(c=fgetc(f)));  // no floats taken into consideration
            goleft();
            strcpy(token,"num");
            return;
        }

        else if(isalpha(c) || c=='_')
        {
            do
            {
                token[i++]=c;
                c=fgetc(f);
            }while(isalnum(c) || c=='_');
            goleft();
            
            if (iskeyword(token))
                return;
            else
            {
                strcpy(token,"id");
                return;
            }
        }

        else if(ispunct(c))
        {
            token[0]=c;
            return;
        }

    }
}

void main(char argc, char *args[])
{
    f = fopen(args[1],"r");
    while(1)
    {
        getNextToken();
        if (cmp(token,"EOF"))
            break;
        printf("line %d: %s\n",line,token);
    }
}