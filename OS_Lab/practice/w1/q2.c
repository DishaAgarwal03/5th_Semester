#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *args[])
{
    int f;
    int l=0, k=0, m=0;
    char line[200];
    char c;

    for(int i=1;i<argc;i++)
    {
        f=open(args[i],O_RDONLY);
        k=0;
        while(read(f,&c,1)==1)
        {
            if(c!='\n')
                line[k++]=c;
            else
            {
                line[k]='\0';
                k=0;
                l++;
                printf("Line %d: %s\n",m*20+l,line);
                if(l==20)
                {
                    fgetc(stdin);
                    l=0;
                    m++;
                }
            }
        }
    }

}
