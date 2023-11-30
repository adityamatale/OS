#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

// Buffer for shared data
int buffer[BUFFER_SIZE];
int itemCount = 0;  // Number of items in the buffer

// Semaphores for synchronization
sem_t mutex;          // Controls access to the critical section
sem_t emptySlots;     // Counts the number of empty slots in the buffer
sem_t filledSlots;    // Counts the number of filled slots in the buffer

// Number of items to produce and consume
#define NUM_ITEMS 10

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&filledSlots, 0, 0);

    pthread_t producerThread, consumerThread;

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);

    return 0;
}

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce item
        int producedItem = rand() % 100;

        // Wait for an empty slot in the buffer
        sem_wait(&emptySlots);

        // Enter critical section
        sem_wait(&mutex);

        // Put the item into the buffer
        buffer[itemCount++] = producedItem;

        // Exit critical section
        sem_post(&mutex);

        // Signal that a slot is filled
        sem_post(&filledSlots);

        printf("Produced item: %d\n", producedItem);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Wait for a filled slot in the buffer
        sem_wait(&filledSlots);

        // Enter critical section
        sem_wait(&mutex);

        // Consume item from the buffer
        int consumedItem = buffer[--itemCount];

        // Exit critical section
        sem_post(&mutex);

        // Signal that an empty slot is available
        sem_post(&emptySlots);

        printf("Consumed item: %d\n", consumedItem);
    }

    pthread_exit(NULL);
}
