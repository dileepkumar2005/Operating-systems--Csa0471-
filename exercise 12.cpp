#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N]; // Mutex locks for each fork
pthread_t philosophers[N]; // Philosopher threads

// Function to simulate thinking
void think(int philosopher) {
    printf("Philosopher %d is thinking...\n", philosopher);
    sleep(1);
}

// Function to simulate eating
void eat(int philosopher) {
    printf("Philosopher %d is eating...\n", philosopher);
    sleep(2);
}

// Philosopher thread function
void* philosopher(void* arg) {
    int philosopher = *((int*) arg);
    
    while (1) {
        think(philosopher); // Philosopher is thinking
        
        // Pick up left fork
        pthread_mutex_lock(&forks[philosopher]);
        printf("Philosopher %d picked up left fork.\n", philosopher);
        
        // Pick up right fork
        pthread_mutex_lock(&forks[(philosopher + 1) % N]);
        printf("Philosopher %d picked up right fork.\n", philosopher);
        
        eat(philosopher); // Philosopher is eating
        
        // Put down right fork
        pthread_mutex_unlock(&forks[(philosopher + 1) % N]);
        printf("Philosopher %d put down right fork.\n", philosopher);
        
        // Put down left fork
        pthread_mutex_unlock(&forks[philosopher]);
        printf("Philosopher %d put down left fork.\n", philosopher);
    }
    
    return NULL;
}

int main() {
    // Initialize mutexes for forks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    
    // Create philosopher threads
    int philosopher_ids[N];
    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    
    // Wait for philosopher threads to finish (they won't finish in this infinite loop)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    
    return 0;
}

