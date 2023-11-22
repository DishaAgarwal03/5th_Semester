#include<stdio.h>
#include<stdlib.h>
#include "LA_helper.c"
// assuming error only from wrong tokens and not multiple tokens 
void prog();
void decl();
void dtype();
void idlist();
void A();
void assign();
void B();

void valid()
{
    printf("\n----------SUCCESS----------\n");
    exit(0);
}

void invalid(char got[], char expected[])
{
    printf("\n----ERROR at line %d: got %s expected %s----\n", line, got, expected);
}

void match(char* expected)
{
    if (cmp(token, expected))
        printf(" <%s> ", token);    
    else
        invalid(token, expected);
    getNextToken();
}

void prog()
{
    getNextToken();
    match("main");
    match("(");
    match(")");
    match("{");
    decl();
    assign();
    
    if (cmp("}", token))
    {
        printf(" <%s> ", token);
        valid();
    }
    else
        invalid(token, "}");
}

void decl()
{
    if (cmp(token, "int") || cmp(token, "char"))
    {
        dtype();
        idlist();
        match(";");
        decl();
    }
}

void dtype()
{
    if (cmp(token, "int") || cmp(token, "char"))
        printf(" <%s> ", token);
    else
        invalid(token, "int or char");
    getNextToken();
}

void idlist()
{
    match("id");
    A();
}

void A()
{
    if (cmp(token, ","))
    {
        printf(" <%s> ", token);
        getNextToken();
        idlist();
    }
}

void assign()
{
    match("id");
    match("=");
    B();
}

void B()
{
    if (cmp(token, "id") || cmp(token, "num"))
        printf(" <%s> ", token);
    else
        invalid(token, "id or num");
    getNextToken();
    match(";");
}

void main(char argc, char *args[])
{
    f = fopen(args[1], "r");
    prog();
}
