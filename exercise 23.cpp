#include <stdio.h>

#define MAX_BLOCKS 10  // Maximum number of blocks
#define MAX_PROCESSES 5  // Maximum number of processes

// Function to implement First Fit algorithm
void firstFit(int blockSize[], int m, int processSize[], int n) {
    // To store the allocated block for each process
    int allocation[n];

    // Initially, no process is allocated any block
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Iterate over all processes and find the first suitable block for each
    for (int i = 0; i < n; i++) {
        // Search for the first block that is large enough to accommodate the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;  // Allocate the block to the process
                blockSize[j] -= processSize[i];  // Update the block size
                break;  // Stop searching once a block is allocated
            }
        }
    }

    // Print the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, blockSize[allocation[i]]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

int main() {
    // Block sizes in memory (size of memory blocks)
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600};

    // Process sizes (size of each process)
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);  // Number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]);  // Number of processes

    // Call firstFit function
    firstFit(blockSize, m, processSize, n);

    return 0;
}

