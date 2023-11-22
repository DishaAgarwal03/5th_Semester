#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3
#define NUM_THREADS 3

// Structure to hold thread arguments
struct ThreadArgs {
    int row;
    int col;
    int (*matrix)[COLS];
};

// Function to add 2 to all elements in a matrix
void* addTwo(void* args) {
    struct ThreadArgs* tArgs = (struct ThreadArgs*)args;

    int row = tArgs->row;
    int col = tArgs->col;
    int (*matrix)[COLS] = tArgs->matrix;

    // Add 2 to each element in the specified row and column
    matrix[row][col] += 2;

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    int matrix[ROWS][COLS];

    // Initialize the matrix
    printf("Enter the elements of the %dx%d matrix:\n", ROWS, COLS);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Display the original matrix
    printf("\nOriginal Matrix:\n");
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // Create thread IDs and attributes
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Create thread arguments
    struct ThreadArgs threadArgs[NUM_THREADS];

    // Create threads to add 2 to matrix elements
    for (int i = 0; i < NUM_THREADS; ++i) {
        threadArgs[i].row = i;
        threadArgs[i].col = i;
        threadArgs[i].matrix = matrix;

        int rc = pthread_create(&threads[i], &attr, addTwo, (void*)&threadArgs[i]);
        if (rc) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Display the modified matrix
    printf("\nModified Matrix (after adding 2 to each element):\n");
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
