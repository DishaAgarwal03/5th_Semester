#include<stdio.h>
#include<stdio.h>
void main(int argc, char *args[])
{
    FILE *f, *fw;
    int pos;
    f=fopen(args[1],"r");
    fw=fopen(args[2],"w+");

    fseek(f,0,SEEK_END);
    pos = ftell(f);
    printf("Size is %d bytes\n",pos);
    fseek(f,0,SEEK_END);

    while(pos>0)
    {
        pos--;
        fseek(f,-1,SEEK_CUR);
        fputc(fgetc(f),fw);
        fseek(f,-1,SEEK_CUR);
    }
}