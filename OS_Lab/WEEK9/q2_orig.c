#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int pid;
    int priority;
    int burst_time;
};

// Queue node structure
struct QueueNode {
    struct Process process;
    struct QueueNode* next;
};

// Define queues for different scheduling policies
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to enqueue a process in a queue
void enqueue(struct Queue* q, struct Process process) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->process = process;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to dequeue a process from a queue
struct Process dequeue(struct Queue* q) {
    if (q->front == NULL) {
        struct Process empty_process = {0, 0, 0};
        return empty_process;
    } else {
        struct QueueNode* temp = q->front;
        struct Process process = temp->process;
        q->front = q->front->next;
        free(temp);
        return process;
    }
}

int main() {
    // Create three queues with different scheduling policies
    struct Queue round_robin_queue = {NULL, NULL};
    struct Queue priority_queue = {NULL, NULL};
    struct Queue fcfs_queue = {NULL, NULL};

    // Add some processes to the queues (you can modify this as needed)
    struct Process process1 = {1, 2, 5};  // Priority: 2
    struct Process process2 = {2, 1, 3};  // Priority: 1
    struct Process process3 = {3, 1, 4};  // Priority: 1

    enqueue(&round_robin_queue, process1); // Queue 1 (Round Robin)
    enqueue(&priority_queue, process2);    // Queue 2 (Priority)
    enqueue(&fcfs_queue, process3);        // Queue 3 (FCFS)

    // Perform scheduling based on the scheduling policy
    while (1) {
        // For demonstration, let's dequeue a process from each queue
        struct Process rr_process = dequeue(&round_robin_queue);
        struct Process pr_process = dequeue(&priority_queue);
        struct Process fcfs_process = dequeue(&fcfs_queue);

        // Process the dequeued processes based on their scheduling policies
        // (You can implement the specific scheduling logic here)

        if (rr_process.burst_time > 0) {
            // Re-enqueue the process with reduced burst time for Round Robin
            enqueue(&round_robin_queue, rr_process);
        }

        if (pr_process.priority > 0) {
            // Re-enqueue the process with reduced priority for Priority scheduling
            enqueue(&priority_queue, pr_process);
        }

        if (fcfs_process.burst_time > 0) {
            // Re-enqueue the process with reduced burst time for FCFS
            enqueue(&fcfs_queue, fcfs_process);
        }

        // Exit the loop if all queues are empty
        if (rr_process.burst_time <= 0 && pr_process.priority <= 0 && fcfs_process.burst_time <= 0) {
            break;
        }
    }

    // You can add more processes and implement specific scheduling logic as needed

    return 0;
}
