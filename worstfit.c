#include <stdio.h>

struct Hole {
    int size;
    int originalSize; // New member to store the original size
    int allocated;
};
struct Process {
    int size;
    int allocatedHole;
};
int main() {
    int nh, np;
    printf("Enter number of holes: ");
    scanf("%d", &nh);
    struct Hole holes[nh];
    for (int i = 0; i < nh; i++) {
        printf("Enter size of hole %d: ", i + 1);
        scanf("%d", &holes[i].size);
        holes[i].originalSize = holes[i].size; // Store the original size
        holes[i].allocated = 0;
    }
    printf("Enter number of processes: ");
    scanf("%d", &np);
    struct Process processes[np];
    for (int i = 0; i < np; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].allocatedHole = -1;
    }
    for (int i = 0; i < np; i++) {
        int worstIndex = -1;
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && holes[j].allocated == 0) {
                if (worstIndex == -1 || holes[j].size > holes[worstIndex].size) {
                    worstIndex = j; // Update worstIndex if a larger hole is found
                }
            }
        }
        if (worstIndex != -1) {
            processes[i].allocatedHole = worstIndex;
            holes[worstIndex].size -= processes[i].size;
            if (holes[worstIndex].size == 0) {
                holes[worstIndex].allocated = 1; // Mark hole as fully allocated if empty
            }
        }
    }
    printf("\nProcess Allocation:\n");
    for (int i = 0; i < np; i++) {
        if (processes[i].allocatedHole != -1) {
            printf("Process %d allocated to Hole %d\n", i + 1, processes[i].allocatedHole + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
    printf("\nActual Holes Availability:\n");
    for (int i = 0; i < nh; i++) {
        printf("Hole %d: Actual Size = %d\n", i + 1, holes[i].originalSize);
    }
    printf("\nCurrent Holes Availability:\n");
    for (int j = 0; j < nh; j++) {
        printf("Hole %d: Current Size = %d\n", j + 1, holes[j].size);
    }
    return 0;
}