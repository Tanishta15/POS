#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    int proc[n][2]; // Array to store burst time and process ID

    // Populate the array with burst times and corresponding process IDs
    for (int i = 0; i < n; i++) {
        proc[i][0] = bt[i]; // burst time
        proc[i][1] = processes[i]; // process ID
    }

    // Sort processes by burst time (SJF logic)
    for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
        if (proc[i][0] > proc[j][0]) {
            // Swap burst time
            int temp = proc[i][0];
            proc[i][0] = proc[j][0];
            proc[j][0] = temp;
            // Swap process ID
            temp = proc[i][1];
            proc[i][1] = proc[j][1];
            proc[j][1] = temp;
        }
    }
    }
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1][0] + wt[i - 1];//update waiting time
    }

    // Restore original order of processes after calculating waiting time
    for (int i = 0; i < n; i++) {
        processes[i] = proc[i][1];
        bt[i] = proc[i][0];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n]; 
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Processes  Burst time  Waiting time  Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", processes[i]);
        printf("          %d ", bt[i]);
        printf("           %d ", wt[i]);
        printf("               %d\n", tat[i]);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average waiting time = %.2f\n", avg_wt);
    printf("Average turn around time = %.2f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {10, 5, 8};
    findAvgTime(processes, n, burst_time);

    return 0;
}