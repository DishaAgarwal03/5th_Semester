#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct mymsg 
{
    long int mtype;
    int a;
};

int ispalin(int a)
{
    int r=0;
    int n=a;
    while(n>0)
    {
        r= (r*10) + (n%10);
        n/=10;
    }
    if(r==a)
        return 1;
    else 
        return 0;
}

int main()
{
    int msgid;
    struct mymsg recv;
    long int recv_msg = 0;
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) 
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(1) 
    {
        if (msgrcv(msgid, (void *)&recv, BUFSIZ, recv_msg, 0) == -1) 
        {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        if(ispalin(recv.a))
            printf("%d is a palindrome number\n",recv.a);
        else
            printf("%d is NOT a palindrome number\n",recv.a);
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1) 
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}