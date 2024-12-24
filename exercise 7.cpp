#include <stdio.h>

struct Process {
    int id;             // Process ID
    int burstTime;      // Burst time of the process
    int arrivalTime;    // Arrival time of the process
    int completionTime; // Completion time of the process
    int waitingTime;    // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

void calculateTimes(struct Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Sorting processes by burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burstTime > processes[j].burstTime) {
                // Swap the processes
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate Completion, Waiting, and Turnaround times
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnaroundTime = processes[0].completionTime - processes[0].arrivalTime;
    processes[0].waitingTime = processes[0].turnaroundTime - processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        // Each process completes after the previous one
        processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Print Process Table
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime, processes[i].arrivalTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / n);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burstTime, &processes[i].arrivalTime);
    }

    // Calculate times and print results
    calculateTimes(processes, n);

    return 0;
}
