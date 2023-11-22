#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3

typedef struct Page {
    int pageNumber;
    int referenceBit;
} Page;

int main() {
    int referenceString[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int referenceStringLength = sizeof(referenceString) / sizeof(referenceString[0]);

    Page frames[NUM_FRAMES];
    int pageFaults = 0;
    int hits = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i].pageNumber = -1;
        frames[i].referenceBit = 0;
    }

    for (int i = 0; i < referenceStringLength; i++) {
        int currentPage = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j].pageNumber == currentPage) {
                frames[j].referenceBit = 1;
                pageFound = 1;
                hits++;
                break;
            }
        }

        if (!pageFound) {
            // Page fault
            pageFaults++;

            // Find the first page with a reference bit of 0 (second chance)
            while (1) {
                int victimIndex = 0;
                if (frames[victimIndex].referenceBit == 0) {
                    break;
                }

                // Give the page a second chance
                frames[victimIndex].referenceBit = 0;

                // Move the page to the end of the queue (circular queue)
                Page temp = frames[0];
                for (int j = 1; j < NUM_FRAMES; j++) {
                    frames[j - 1] = frames[j];
                }
                frames[NUM_FRAMES - 1] = temp;
            }

            // Replace the victim page with the new page
            frames[0].pageNumber = currentPage;
            frames[0].referenceBit = 0;
        }
    }

    // Calculate hit ratio
    double hitRatio = (double)hits / referenceStringLength;

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2lf\n", hitRatio);

    return 0;
}
