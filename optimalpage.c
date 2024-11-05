#include <stdio.h>
#include <stdlib.h>

void optimalPageReplacement(int pages[], int numPages, int numFrames) {
    int *frame = (int *)malloc(numFrames * sizeof(int));
    int *nextUse = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0,i,j;
    for (i = 0; i < numFrames; i++) {
        frame[i] = -1;
    }
    for (i = 0; i < numPages; i++) {
    for (j = 0; j < numFrames; j++) {
        if (frame[j] == pages[i]) {
            break;
        }
    }
    if (j == numFrames) {
        pageFaults++;
        int lruIndex = -1, farthest = -1;
        for (j = 0; j < numFrames; j++) {
            nextUse[j] = -1;
            for (int k = i + 1; k < numPages; k++) {
                if (frame[j] == pages[k]) {
                    nextUse[j] = k;
                    break;
                }
            }
            if (nextUse[j] == -1) {
                lruIndex = j;
                break;
            } else if (nextUse[j] > farthest) {
                farthest = nextUse[j];
                lruIndex = j;
            }
        }
        frame[lruIndex] = pages[i];
    }
    }
    free(frame);
    free(nextUse);
    printf("Number of page faults: %d\numPages", pageFaults);
}

int main() {
    int numFrames, numPages;
    int *pages = (int *)malloc(numPages * sizeof(int));
    printf("Enter number of numFrames: ");
    scanf("%d", &numFrames);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter page numbers: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    optimalPageReplacement(pages, numPages, numFrames);
    free(pages);
    return 0;
}