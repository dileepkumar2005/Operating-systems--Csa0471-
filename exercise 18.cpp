#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer

// Shared buffer and associated variables
int buffer[BUFFER_SIZE];
int in = 0;  // Index for the next item to be produced
int out = 0; // Index for the next item to be consumed

// Semaphores
sem_t empty;  // Semaphore to count the empty spaces in the buffer
sem_t full;   // Semaphore to count the filled spaces in the buffer
sem_t mutex;  // Mutex to ensure mutual exclusion while accessing the buffer

// Producer function
void* producer(void* param) {
    int item;
    while (1) {
        // Produce an item (random number for simplicity)
        item = rand() % 100;
        printf("Producer produced item: %d\n", item);

        // Wait for an empty slot
        sem_wait(&empty);

        // Wait for exclusive access to the buffer
        sem_wait(&mutex);

        // Put the item into the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Release the mutex after modifying the buffer
        sem_post(&mutex);

        // Signal that a new item has been added to the buffer
        sem_post(&full);

        // Sleep to simulate processing time
        sleep(1);
    }
}

// Consumer function
void* consumer(void* param) {
    int item;
    while (1) {
        // Wait for a full slot
        sem_wait(&full);

        // Wait for exclusive access to the buffer
        sem_wait(&mutex);

        // Remove the item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        // Release the mutex after modifying the buffer
        sem_post(&mutex);

        // Signal that a slot is now empty
        sem_post(&empty);

        // Consume the item (just print for simplicity)
        printf("Consumer consumed item: %d\n", item);

        // Sleep to simulate processing time
        sleep(2);
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);             // Initially no item is in the buffer
    sem_init(&mutex, 0, 1);            // Mutex to control access to the buffer

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join the threads (this will never be reached in this infinite loop)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

