#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
    pid_t pid;  
    int status;

    pid=fork(); 
    if(pid==-1)
    {
        printf("Error in forking q2\n");
        exit(-1);
    }
    else if(pid==0)
    {
        printf("Child q2 executing ouput file of q1:\n");
        execlp("./q1","./q1",NULL);
        // OR execl("q1","./q1",NULL); when terminal open in the same directory I guess
    }
    else
    {
        wait(&status);  
        //if don't put wait then nothing from q2 will be printed.
        //Be it child process or parent process. 
        //Only exec() file will be executed.
        printf("Parent q2\n");
    }
}