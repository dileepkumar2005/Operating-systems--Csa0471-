#include <stdio.h>
#include <pthread.h>

// Thread function
void *print_message(void *msg) {
    printf("%s\n", (char *)msg);
    return NULL;
}

int main() {
    pthread_t thread;  // Declare thread ID
    const char *message = "Hello from the thread!";
    
    // Create a new thread
    pthread_create(&thread, NULL, print_message, (void *)message);
    
    // Wait for the thread to finish (join)
    pthread_join(thread, NULL);
    
    printf("Main thread exits\n");
    
    return 0;
}

