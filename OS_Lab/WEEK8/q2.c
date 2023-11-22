// NOT WORKING

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include "q2shm.h"

void main()
{
    pid_t pid; 
    int status;
    void *smem = (void *)0;
    struct shared *smsg;
    int shmid,run=1;
    shmid = shmget((key_t)1234, sizeof(struct shared), 0666 | IPC_CREAT);    // create shared memory

    pid=fork(); 
    if(pid==-1)
    {
        printf("Error in forking\n");
        exit(-1);
    }
    else if(pid==0)
    {
        // Child process
        smem = shmat(shmid, (void *)0, 0);
        smsg = (struct shared *)smem;
        smsg->c = 0;
        while(run)
        {
            if (smsg->c) 
            {
                if(smsg->alpha=='z')
                    smsg->alpha='a';
                else if (smsg->alpha=='Z')
                    smsg->alpha='A';
                else
                    smsg->alpha+=1;
                sleep( rand() % 4 ); /* make the other process wait for us ! */
                smsg->c = 0;
                run=0;
            }
        }
        exit(0);
    }
    else
    {
        // Parent process
        smem = shmat(shmid, (void *)0, 0);
        smsg = (struct shared *)smem;

        while(smsg->c == 1) 
        {
            sleep(1);
            printf("Waiting for client...\n");
        }
        printf("Enter some alphabet: ");
        scanf("%c",&smsg->alpha);
        smsg->c = 1;
        while(smsg->c==1);
        printf("Updated value: %c\n",smsg->alpha);
        wait(NULL);
    }
}