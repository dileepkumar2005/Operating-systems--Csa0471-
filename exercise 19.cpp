#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5  // Number of threads (processes)
#define INITIAL_BALANCE 1000  // Initial bank balance

// Global variables
int bank_balance = INITIAL_BALANCE;  // Shared bank balance
pthread_mutex_t mutex;  // Mutex for synchronizing access to bank_balance

// Function for deposit operation
void* deposit(void* arg) {
    int amount = rand() % 100 + 1;  // Random deposit amount (1-100)
    pthread_mutex_lock(&mutex);  // Lock the mutex before modifying the shared resource

    bank_balance += amount;  // Update the bank balance
    printf("Deposited: $%d, New Balance: $%d\n", amount, bank_balance);

    pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying the shared resource
    return NULL;
}

// Function for withdrawal operation
void* withdraw(void* arg) {
    int amount = rand() % 100 + 1;  // Random withdrawal amount (1-100)

    // Ensure there is enough balance for withdrawal
    pthread_mutex_lock(&mutex);  // Lock the mutex before modifying the shared resource
    if (bank_balance >= amount) {
        bank_balance -= amount;  // Update the bank balance
        printf("Withdrawn: $%d, New Balance: $%d\n", amount, bank_balance);
    } else {
        printf("Attempted Withdrawal: $%d, Insufficient Balance: $%d\n", amount, bank_balance);
    }
    pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying the shared resource
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];  // Array to hold thread identifiers
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    // Create threads for deposit and withdrawal operations
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, deposit, NULL);  // Deposit thread
        } else {
            pthread_create(&threads[i], NULL, withdraw, NULL);  // Withdrawal thread
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex after use
    pthread_mutex_destroy(&mutex);

    // Final balance display
    printf("Final Bank Balance: $%d\n", bank_balance);

    return 0;
}

