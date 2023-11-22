#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>  //for sleep()
#define size 10

int buf[size],f,r;
sem_t mutex,wrt;
int readcount=0;
char ch='A';

void *writer(void *arg)
{
    while(1)
    {
       
        sem_wait(&wrt);
        ch++;
        printf("Writing %c\n",ch);
        sem_post(&wrt);
        sleep(1);

    }
}

void *reader(void *arg)
{
    while(1)
    {
        sem_wait(&mutex);
        readcount++;
        if(readcount==1)
            sem_wait(&wrt);
        sem_post(&mutex);
        printf("Reading %c\n",ch);
        sem_wait(&mutex);
        readcount--;
        if(readcount==0)
            sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);  

    pthread_create(&tid1, NULL, writer, NULL);
    pthread_create(&tid2, NULL, reader, NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

}
