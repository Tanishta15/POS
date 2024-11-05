#include <stdio.h>
#include <stdlib.h>

void fifoPageReplacement(int pages[], int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0, index = 0, i, j, found;
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    for (i = 0; i < numPages; i++) {
        found = 0;
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % numFrames;
            pageFaults++;
        }
    }
    free(frames);
    printf("Number of page faults: %d\n", pageFaults);
}
int main() {
    int numFrames, numPages;
    int *pages = (int *)malloc(numPages * sizeof(int));
    printf("Enter number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter page numbers: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    fifoPageReplacement(pages, numPages, numFrames);
    free(pages);
    return 0;
}