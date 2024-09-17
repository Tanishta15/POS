#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
} Process;

void sortByArrival(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void findCompletionTimes(Process processes[], int n) {
    int currentTime = 0, completed = 0;
    
    while (completed != n) {
        int idx = -1;
        int highestPriority = -1;
        
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].isCompleted == 0) {
            if (processes[i].priority > highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
            // In case of tie in priority, choose the one that arrived first
            if (processes[i].priority == highestPriority && idx != -1) {
                if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                    idx = i;
                }
            }
        }
    }
        
        if (idx != -1) {
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            processes[idx].isCompleted = 1;
            completed++;
            currentTime = processes[idx].completionTime;
        } else {
            currentTime++;
        }
    }
}

void findAverageTimes(Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    findCompletionTimes(processes, n);
    
    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
    
    printf("\nAverage waiting time: %.2f", totalWaitingTime / n);
    printf("\nAverage turnaround time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    Process processes[MAX];
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", processes[i].id);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].isCompleted = 0;
    }
    
    sortByArrival(processes, n);
    findAverageTimes(processes, n);
    
    return 0;
}