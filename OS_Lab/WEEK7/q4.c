#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define chairs 5

sem_t cust;  // Semaphore to represent the number of waiting customers
sem_t barber;     // Semaphore to represent the barber availability
sem_t mutex;      // Semaphore for mutual exclusion

int c;

int cust_wait = 0;  // Number of customers waiting

// Function to simulate customer threads
void *customer(void *arg) {
    int custid = *(int *)arg;

    sem_wait(&mutex);
    if (cust_wait == chairs) {
        printf("Customer %d is leaving as there are no available chairs.\n", custid);
        sem_post(&mutex);
        return NULL;
    }

    cust_wait++;
    printf("Customer %d has entered the shop and is waiting. Chairs available: %d\n", custid, chairs - cust_wait);
    sem_post(&mutex);

    sem_post(&cust);  // Signal the barber that a customer is waiting
    sem_wait(&barber);     // Wait for the barber to become available
    
    printf("Customer %d is getting a haircut.\n", custid);

    sem_post(&mutex);
    cust_wait--;
    sem_post(&mutex);
    
    return NULL;
}

// Function to simulate the barber thread
void *barber_thread(void *arg) {
    while (1) {
        sem_wait(&cust);  // Wait for a customer to arrive

        // Serve the customer for some time
        printf("Barber is cutting hair.\n");
        sleep(3);

        sem_post(&barber);  // Signal the customer that the haircut is done
    }
}

int main() {
    // Initialize the semaphores
    sem_init(&cust, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t barber_tid;
    pthread_t customer_tid[chairs];

    // Create the barber thread
    pthread_create(&barber_tid, NULL, barber_thread, NULL);

    // Create customer threads
    int custids[chairs];
    for (int i = 0; i < chairs; i++) {
        custids[i] = i + 1;
        pthread_create(&customer_tid[i], NULL, customer, &custids[i]);
    }

    // Wait for all customer threads to finish
    for (int i = 0; i < chairs; i++) {
        pthread_join(customer_tid[i], NULL);
    }

    // Terminate the barber thread
    pthread_cancel(barber_tid);
    pthread_join(barber_tid, NULL);

    // Destroy the semaphores
    sem_destroy(&cust);
    sem_destroy(&barber);
    sem_destroy(&mutex);

    return 0;
}