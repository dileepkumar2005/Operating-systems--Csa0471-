#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 5  // Maximum size of the buffer
int buffer[MAX_BUFFER_SIZE];
int in = 0, out = 0;  // Indices to track the next slot to produce and consume

sem_t empty, full, mutex;  // Semaphores

// Function to simulate the producer
void *producer(void *param) {
    int item;
    
    while (1) {
        item = rand() % 100;  // Produce a random item
        
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        
        // Wait for mutual exclusion to access the buffer
        sem_wait(&mutex);
        
        // Add item to buffer
        buffer[in] = item;
        printf("Produced: %d at position %d\n", item, in);
        in = (in + 1) % MAX_BUFFER_SIZE;  // Circular increment
        
        // Release mutex and signal that a new item is produced
        sem_post(&mutex);
        sem_post(&full);
        
        sleep(1);  // Simulate time taken to produce an item
    }
}

// Function to simulate the consumer
void *consumer(void *param) {
    int item;
    
    while (1) {
        // Wait for a filled slot in the buffer
        sem_wait(&full);
        
        // Wait for mutual exclusion to access the buffer
        sem_wait(&mutex);
        
        // Consume an item from the buffer
        item = buffer[out];
        printf("Consumed: %d from position %d\n", item, out);
        out = (out + 1) % MAX_BUFFER_SIZE;  // Circular increment
        
        // Release mutex and signal that an item has been consumed
        sem_post(&mutex);
        sem_post(&empty);
        
        sleep(2);  // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize semaphores
    sem_init(&empty, 0, MAX_BUFFER_SIZE);  // Buffer starts with all empty slots
    sem_init(&full, 0, 0);  // Buffer starts with no full slots
    sem_init(&mutex, 0, 1);  // Mutex initialized to 1 (binary semaphore)
    
    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for threads to finish (they won't finish in this case, infinite loop)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destroy semaphores (not reached in this case due to infinite loop)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}

