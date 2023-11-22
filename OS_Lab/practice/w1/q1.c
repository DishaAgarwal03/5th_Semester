#include<fcntl.h>
#include<unistd.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *args[])
{
    int f, fl=0;
    char c;
    char line[300];
    char *a;
    int i=0,k=0;

    f=open(args[1],O_RDONLY);
    if(f<0)
    {
        printf("Error");
        exit(0);
    }
    while(read(f,&c,1)==1)
    {
        if(c!='\n')
        {
            line[k++]=c;
        }
        else
        {
            line[k]='\0';
            k=0;
            i++;
            if(a=strstr(line,args[2]))
            {
                fl=1;
                if((a[-1]==' ' || a[-1]=='\0') && (a[strlen(args[2])]==' ' || a[strlen(args[2])]=='\n' || a[strlen(args[2])]=='\0'))
                    printf("Line %d:   %s\n",i,line);
            }
        }
    }
    if (!fl)
        printf("No line has the word\n");
}
