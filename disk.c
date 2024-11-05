#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int distance = 0, current_head = head;
    printf("FCFS Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", requests[i]);
        distance += abs(current_head - requests[i]);
        current_head = requests[i];
    }
    printf("\nTotal Seek Distance: %d\n", distance);
}

void sstf(int requests[], int n, int head) {
    int completed[n];
    int distance = 0, current_head = head;
    for (int i = 0; i < n; i++) completed[i] = 0;

    printf("SSTF Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        int min_distance = 9999, min_index = -1;
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(current_head - requests[j]) < min_distance) {
                min_distance = abs(current_head - requests[j]);
                min_index = j;
            }
        }
        printf("%d -> ", requests[min_index]);
        distance += min_distance;
        current_head = requests[min_index];
        completed[min_index] = 1;
    }
    printf("\nTotal Seek Distance: %d\n", distance);
}

void sort_requests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int distance = 0, current_head = head;
    sort_requests(requests, n);

    printf("SCAN Seek Sequence: ");
    if (direction == 1) {  // Moving towards the end
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
        printf("%d -> ", disk_size - 1);  // Move to the end of the disk
        distance += abs(current_head - (disk_size - 1));
        current_head = disk_size - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
    } else {  // Moving towards the beginning
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
        printf("0 -> ");  // Move to the start of the disk
        distance += current_head;  // distance to 0
        current_head = 0;

        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
    }
    printf("\nTotal Seek Distance: %d\n", distance);
}


void look(int requests[], int n, int head, int direction) {
    int distance = 0, current_head = head;
    sort_requests(requests, n);

    printf("LOOK Seek Sequence: ");
    if (direction == 1) {  // Moving towards the end
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
    } else {  // Moving towards the beginning
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                printf("%d -> ", requests[i]);
                distance += abs(current_head - requests[i]);
                current_head = requests[i];
            }
        }
    }
    printf("\nTotal Seek Distance: %d\n", distance);
}

void c_scan(int requests[], int n, int head, int disk_size) {
    int distance = 0, current_head = head;
    sort_requests(requests, n);

    printf("C-SCAN Seek Sequence: ");
    // Move towards the end of the disk
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            printf("%d -> ", requests[i]);
            distance += abs(current_head - requests[i]);
            current_head = requests[i];
        }
    }
    
    // Move to the end of the disk, and then jump to 0
    printf("%d -> ", disk_size - 1);
    distance += abs(current_head - (disk_size - 1));
    current_head = 0;
    printf("0 -> ");
    
    // Continue servicing from the start of the disk
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            printf("%d -> ", requests[i]);
            distance += abs(current_head - requests[i]);
            current_head = requests[i];
        }
    }
    
    printf("\nTotal Seek Distance: %d\n", distance);
}

void c_look(int requests[], int n, int head) {
    int distance = 0, current_head = head;
    sort_requests(requests, n);

    printf("C-LOOK Seek Sequence: ");
    // Move towards the end of the request list
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            printf("%d -> ", requests[i]);
            distance += abs(current_head - requests[i]);
            current_head = requests[i];
        }
    }
    
    // Jump back to the start of the request list (smallest unprocessed request)
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            printf("%d -> ", requests[i]);
            distance += abs(current_head - requests[i]);
            current_head = requests[i];
        }
    }
    
    printf("\nTotal Seek Distance: %d\n", distance);
}

int main() {
    int n, head, disk_size, direction, choice;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    do {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, n, head);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                scan(requests, n, head, disk_size, direction);
                break;
            case 4:
                c_scan(requests, n, head, disk_size);
                break;
            case 5:
                look(requests, n, head, direction);
                break;
            case 6:
                c_look(requests, n, head);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 7);

    return 0;
}