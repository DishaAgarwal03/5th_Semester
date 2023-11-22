#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
    pid_t pid,prpid,ppid,cpid;  
    int status;

    pid=fork(); 
    if(pid==-1)
    {
        printf("Error in forking\n");
        exit(-1);
    }
    else if(pid>0)
    {
        prpid=getpid();
        ppid=getppid();
        cpid=pid;
        printf("\nPARENT PROCESS: \nParent PID -> %d \nProcess ID -> %d \nChild PID-> %d \n",ppid,prpid,cpid);
    }
    else
    {
        prpid=getpid();
        ppid=getppid();
        printf("\nCHILD PROCESS: \nParent PID -> %d \nProcess ID -> %d \n\n",ppid,prpid);
        exit(0);
    }
}