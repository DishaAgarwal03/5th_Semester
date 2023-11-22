#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>  //for sleep()

//full : number of filled slots
//empty : number of emnpty slots


int buf,f,r;
sem_t mutex,sema,semb;

void *A(void *arg)
{
    printf("Waiting for B\n");
    sem_wait(&semb);

    sem_wait(&mutex);
    printf("Entered A\n");
    sleep(1);
    sem_post(&mutex);

    sem_post(&sema);
}

void *B(void *arg)
{
    printf("Waiting for A\n");
    sem_wait(&sema);

    sem_wait(&mutex);
    printf("Entered B\n");
    sleep(1);
    sem_post(&mutex);

    sem_post(&semb);
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&mutex,0,1);
    sem_init(&sema,0,0); 
    sem_init(&semb,0,0); 

    pthread_create(&tid1, NULL, A, NULL);
    pthread_create(&tid2, NULL, B, NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

}
