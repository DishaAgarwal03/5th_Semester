#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
struct mymsg 
{
    long int mtype;
    int a;
};
int main()
{
    struct mymsg sendd;
    int msgid;
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) 
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Enter a number:");
        scanf("%d",&sendd.a);
        sendd.mtype = 1;

        if (msgsnd(msgid, (void *)&sendd, MAX_TEXT, 0) == -1) 
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
    }
        
    exit(EXIT_SUCCESS);
}