#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

// Buffer for shared data
int buffer[BUFFER_SIZE];
int itemCount = 0;  // Number of items in the buffer

// Mutex for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Condition variables for signaling
pthread_cond_t bufferNotFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferNotEmpty = PTHREAD_COND_INITIALIZER;

// Number of items to produce and consume
#define NUM_ITEMS 10

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);

int main() {
    pthread_t producerThread, consumerThread;

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce item
        int producedItem = rand() % 100;

        // Acquire the mutex before accessing the buffer
        pthread_mutex_lock(&mutex);

        // Wait until the buffer is not full
        while (itemCount == BUFFER_SIZE) {
            pthread_cond_wait(&bufferNotFull, &mutex);
        }

        // Put the item into the buffer
        buffer[itemCount++] = producedItem;

        // Signal that the buffer is not empty
        pthread_cond_signal(&bufferNotEmpty);

        // Release the mutex
        pthread_mutex_unlock(&mutex);

        printf("Produced item: %d\n", producedItem);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Acquire the mutex before accessing the buffer
        pthread_mutex_lock(&mutex);

        // Wait until the buffer is not empty
        while (itemCount == 0) {
            pthread_cond_wait(&bufferNotEmpty, &mutex);
        }

        // Consume item from the buffer
        int consumedItem = buffer[--itemCount];

        // Signal that the buffer is not full
        pthread_cond_signal(&bufferNotFull);

        // Release the mutex
        pthread_mutex_unlock(&mutex);

        printf("Consumed item: %d\n", consumedItem);
    }

    pthread_exit(NULL);
}
