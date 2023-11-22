#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
    pid_t pid;  
    pid=fork(); 
    if(pid==-1)
    {
        printf("Error in forking\n");
        exit(-1);
    }
    else if(pid==0)
    {
        printf("Child PID: %d \n",getpid());
        exit(0);
    }
    else
    {
        //no corresponding wait in sleeping parent
        printf("\nParent PID: %d \n",getpid());
        sleep(10);
    }
}