#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<unistd.h>

#include<sys/stat.h>  //for S_IRUSR and S_IWUSR

int main(int argc, char *args[])
{
    int f1, f2;
    char c;

    f1=open(args[1],O_RDONLY);
    f2=open(args[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR );

    if(f1<0 || f2<0)
    {
        printf("Error");
        exit(1);
    }

    while(read(f1,&c,1)==1)
    {
        write(f2,&c,1);
    }

}
