#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

// Matrix dimensions
#define ROWS 3
#define COLS 3

// Maximum number of threads
#define MAX_THREADS 4

// Matrix variables
int matrixA[ROWS][COLS];
int matrixB[ROWS][COLS];
int resultMatrix[ROWS][COLS];

// Structure to hold thread information
typedef struct {
    int start_row;
    int end_row;
} ThreadInfo;

// Function prototypes
void fillMatrix(int matrix[ROWS][COLS]);
void printMatrix(int matrix[ROWS][COLS]);
void *matrixAddition(void *arg);

int main() {
    pthread_t threads[MAX_THREADS];
    ThreadInfo threadInfo[MAX_THREADS];

    // Initialize matrices
    fillMatrix(matrixA);
    fillMatrix(matrixB);

    // Print matrices
    printf("Matrix A:\n");
    printMatrix(matrixA);

    printf("Matrix B:\n");
    printMatrix(matrixB);

    // Create threads for matrix addition
    int rowsPerThread = ROWS / MAX_THREADS;
    for (int i = 0; i < MAX_THREADS; i++) {
        threadInfo[i].start_row = i * rowsPerThread;
        threadInfo[i].end_row = (i == MAX_THREADS - 1) ? ROWS : (i + 1) * rowsPerThread;

        pthread_create(&threads[i], NULL, matrixAddition, (void *)&threadInfo[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix
    printf("Result Matrix (Sum of A and B):\n");
    printMatrix(resultMatrix);

    return 0;
}

void fillMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 10; // Filling matrix with random values for demonstration
        }
    }
}

void printMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *matrixAddition(void *arg) {
    ThreadInfo *threadInfo = (ThreadInfo *)arg;

    for (int i = threadInfo->start_row; i < threadInfo->end_row; i++) {
        for (int j = 0; j < COLS; j++) {
            resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    pthread_exit(NULL);
}
