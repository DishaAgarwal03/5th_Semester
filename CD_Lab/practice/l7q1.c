#include<stdio.h>
#include<stdlib.h>
#include "LA_helper.c"

void prog();
void decl();
void dtype();
void idlist();
void A();
void assign();
void B();
// void decl();
// void decl();
// void decl();
// void decl();
// void decl();

void valid()
{
    printf("\n----------SUCCESS----------\n");
    exit(0);
}

void invalid(char got[], char expected[])
{
    printf("\n----ERROR at line %d: got %s expected %s----\n", line, got, expected);
    return;
}

void prog()
{
    getNextToken();
    if(cmp("main",token))
    {
        printf(" <%s> ",token);
        getNextToken();
        if(cmp("(",token))
        {
            printf(" <%s> ",token);
            getNextToken();
            if(cmp(")",token))
            {
                printf(" <%s> ",token);
                getNextToken();
                if(cmp("{",token)) 
                {
                    printf(" <%s> ",token);
                    getNextToken();
                    decl();
                    assign();
                    if(cmp("}",token))
                    {
                        printf(" <%s> ",token);
                        getNextToken();
                        valid();
                    }
                    else
                        invalid(token,"}");
                }
                else
                    invalid(token,"{");
            }
            else
                invalid(token,")");
        }
        else
            invalid(token,"(");
    }
    else
        invalid(token,"main");
}

void decl()
{
    if(cmp(token,"int")||cmp(token,"char"))
    {
        dtype();
        idlist();
        if(cmp(token,";"))
        {
            printf(" <%s> ",token);
            getNextToken();
            decl();
        }
        else
            invalid(token,";");
    }
}

void dtype()
{
    if(cmp(token,"int")||cmp(token,"char"))
    {
        printf(" <%s> ",token);
        getNextToken();
        return;
    }
    else
        invalid(token,"int or char");
}

void idlist()
{
    if(cmp(token,"id"))
    {
        printf(" <%s> ",token);
        getNextToken();
        A();
    }
    else
        invalid(token,"id");
}

void A()
{
    if(cmp(token,","))
    {
        printf(" <%s> ",token);
        getNextToken();
        idlist();
    }
}

void assign()
{
    if(cmp(token,"id"))
    {
        printf(" <%s> ",token);
        getNextToken();
        if(cmp(token,"="))
        {
            printf(" <%s> ",token);
            getNextToken();
            B();
        }
        else
            invalid(token,"=");
    }
    else
        invalid(token,"id");
}

void B()
{
    if(cmp(token,"id") || cmp(token,"num"))
    {
        printf(" <%s> ",token);
        getNextToken();
        if(cmp(token,";"))
        {
            printf(" <%s> ",token);
            getNextToken();
            return;
        }
        else
            invalid(token,";");
    }
    else
        invalid(token,"id or num");
}

void main(char argc, char *args[])
{
    f = fopen(args[1],"r");
    prog();
}