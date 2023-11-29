#include <stdio.h>

// Function to perform priority scheduling
void priorityScheduling(int processes[], int burst_time[], int priority[], int n) {
    // Sort the processes based on priority (higher priority first) using Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                // Swap the processes
                int temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;

                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;

                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;
            }
        }
    }

    // Calculate the waiting time and turnaround time
    int waiting_time[n];
    int turnaround_time[n];

    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];

    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    // Calculate the average waiting time and average turnaround time
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Display the results
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int priority[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter the details for Process %d:\n", i + 1);
        processes[i] = i + 1;
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    // Perform priority scheduling
    priorityScheduling(processes, burst_time, priority, n);

    return 0;
}
