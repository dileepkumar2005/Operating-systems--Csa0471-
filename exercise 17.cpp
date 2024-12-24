#include <stdio.h>
#include <stdbool.h>

// Maximum number of processes and resources
#define P 5  // Number of processes
#define R 3  // Number of resources

// Function to check if the system is in a safe state
bool isSafe(int available[], int max[][R], int allocation[][R], int need[][R]) {
    int work[R], finish[P];
    
    // Initialize the work and finish arrays
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < P; i++) {
        finish[i] = 0;  // Mark all processes as not finished
    }

    // Try to find a process that can finish
    int count = 0; // Count of finished processes
    while (count < P) {
        bool progressMade = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {  // Process i is not finished
                bool canFinish = true;
                // Check if process i can finish with the available resources
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    // Add allocated resources to work
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;  // Mark process i as finished
                    count++;
                    progressMade = true;
                    break;  // Restart search for another process that can finish
                }
            }
        }
        
        if (!progressMade) {
            return false;  // No process can finish, so the system is not in a safe state
        }
    }
    return true;  // All processes can finish, system is in a safe state
}

// Function to request resources
bool requestResources(int process, int request[], int available[], int max[][R], int allocation[][R], int need[][R]) {
    // Check if request is less than or equal to the need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }
    
    // Check if request is less than or equal to the available resources
    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Error: Not enough resources available.\n");
            return false;
        }
    }

    // Pretend to allocate the resources
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is in a safe state
    if (isSafe(available, max, allocation, need)) {
        printf("Request granted.\n");
        return true;
    } else {
        // Rollback if not safe
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request cannot be granted, system would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    // Available resources
    int available[] = {3, 3, 2};  // For example: 3 instances of resource 1, 3 of resource 2, 2 of resource 3

    // Maximum resources required by each process
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Currently allocated resources
    int allocation[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Remaining needs of each process
    int need[][R] = {
        {7, 4, 3},
        {1, 2, 2},
        {6, 0, 0},
        {0, 1, 1},
        {4, 3, 1}
    };

    // Process requests for resources
    int request1[] = {1, 0, 2};  // Process 1 requests 1 unit of resource 1, 0 of resource 2, 2 of resource 3
    requestResources(1, request1, available, max, allocation, need);

    int request2[] = {2, 1, 1};  // Process 3 requests 2 units of resource 1, 1 of resource 2, and 1 of resource 3
    requestResources(3, request2, available, max, allocation, need);

    return 0;
}

