#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>  
#include <unistd.h> 
#include "bankers_algo.c"

pthread_t tid[n];  // n threads for n processes
int counter; 
pthread_mutex_t lock; 
  
void* banker(void* arg) 
{ 
    int i = (int) arg;
    int ch;

    while(1)
    {
        pthread_mutex_lock(&lock); 
        printf("\nEnter choice for Process %d: ", i);
        scanf("%d", &ch);
        pthread_mutex_unlock(&lock); 
        if (ch==1)
        {
            pthread_mutex_lock(&lock); 

            int req[m];
            printf("Enter request for Process %d: ",i);
            for(int j=0; j<m; j++)
                scanf("%d", &req[j]);
            if (accept_request(req, i))
            {
                printf("\nThe request of Process %d can be granted immediately\nUpdated Values:");
                display();
            }
            else
                printf("\nThe request of Process %d cannot be granted immediately\n");
            sleep(1);

            pthread_mutex_unlock(&lock); 
        }
        else if (ch==2)
        {
            sleep(10);
        }
        else
            return NULL;
    }
} 
  
void main(void) 
{ 
    int i = 0; 
    int error; 
    update_need();

    pthread_mutex_init(&lock, NULL);  // creating a lock

    printf("1. Make a request \n2. Wait \n3. Exit\n");

    for(i=0; i<n; i++)                           // creating n threads
        pthread_create(&(tid[i]), NULL, &banker, (void*)i); 
    
    for(i=0; i<n; i++) 
        pthread_join(tid[i], NULL); 

    pthread_mutex_destroy(&lock);   //destroying the lock 
} 



