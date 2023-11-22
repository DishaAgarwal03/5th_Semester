#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#include<sys/wait.h>

int main()
{
    pid_t pid;
    pid=fork();

    if(pid==0)
    {
        //child
        printf("Child=> ppid: %d; pid:%d\n",getppid(),getpid());
        exit(EXIT_SUCCESS);
    }
    if(pid>0)
    {
        wait(NULL);
        printf("Parent => ppid:%d; pid:%d; cpid: %d\n",getppid(),getpid(),pid);
        
        printf("Child process finished..terminating\n");
    }
    else
        printf("Error");
    return EXIT_SUCCESS;
}

