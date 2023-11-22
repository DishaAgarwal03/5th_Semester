#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>  //for sleep()
#define size 10

//full : number of filled slots
//empty : number of emnpty slots


int buf[size],f,r;
sem_t mutex,full,empty;
int c=0,p=0;

void *produce(void *arg)
{
    while(1)
    {
        for(int i=0;i<c+10;i++)
        {
        sem_wait(&empty);
        sem_wait(&mutex);
        p++;
        printf("Produced : %d\n",p);
        buf[(++r)%size]=p;
        usleep(100000);
        sem_post(&mutex);
        sem_post(&full);
        // printf("Full %u\n",full);
        }
        sleep(1);
    }
}

void *consume(void *arg)
{
    while(1)
    {
        sem_wait(&full);
        // printf("Full %d\n",full);
        sem_wait(&mutex);
        c++;
        int item=buf[(++f)%size];
        printf("Consumed : %d\n",item);
        usleep(100000);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&mutex,0,1);
    sem_init(&full,0,0);  
    sem_init(&empty,0,size);

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consume, NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

}
