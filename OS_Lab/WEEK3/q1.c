#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
    pid_t pid;  //in <sys/types.h>
    int status;

    pid=fork(); //in <unistd.h>
    if(pid==-1)
    {
        printf("Error in forking\n");
        exit(-1);
    }
    else if(pid==0)
    {
        printf("Blocked the parent...\n");
        for(int i=0;i<2;i++)
            printf("Child\n");
        exit(0);
    }
    else
    {
        wait(&status);  //in <sys/wait.h>
        printf("Unblocked the parent...\n");
        for(int i=0;i<2;i++)
            printf("Parent\n");
        exit(0);
    }
}