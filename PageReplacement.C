#include <stdio.h>
#include <stdbool.h>
#define MAX_FRAMES 10 // Maximum number of frames in memory
// Function to find the index of the least recently used page
int findLRU(int time[], int n)
{
    int min = time[0], idx = 0;
    for (int i = 1; i < n; i++)
    {
        if (time[i] < min)
         {
            min = time[i];
            idx = i;
        }
    }
    return idx;
}
int main()
{
    int n; // Number of pages in the reference string
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n]; // Page reference string
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    int numFrames; // Number of frames in memory
    printf("Enter the number of page frames: ");
    scanf("%d", &numFrames);
    int frames[MAX_FRAMES]; // Array to hold the frames in memory
    int time[MAX_FRAMES];   // Array to hold the time of last use for LRU
    int pageFaultsFIFO = 0, pageFaultsLRU = 0, pageFaultsOptimal = 0;
    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1; // Initialize frames with an invalid page number
        time[i] = 0;    // Initialize time for LRU
    }
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in memory
        for (int j = 0; j < numFrames; j++)
            {
            if (frames[j] == page)
             {
                found = 1;
                time[j] = i; // Update the time of last use for LRU
                break;
            }
        }
        // If the page is not in memory, perform page replacement
        if (!found)
            {
            // FIFO
            frames[pageFaultsFIFO % numFrames] = page;
            pageFaultsFIFO++;
            // LRU
            int lruIndex = findLRU(time, numFrames);
            frames[lruIndex] = page;
            time[lruIndex] = i;
            pageFaultsLRU++;
            // Optimal
            int future[MAX_FRAMES] = {0};
            for (int j = 0; j < numFrames; j++)
                {
                for (int k = i + 1; k < n; k++)
                {
                    if (pages[k] == frames[j])
                    {
                        future[j] = k;
                        break;
                    }
                }
            }
            int optimalIndex = 0;
            int maxFuture = future[0];
            for (int j = 1; j < numFrames; j++)
            {
                if (future[j] == 0)
                {
                    optimalIndex = j;
                    break;
                }
                if (future[j] > maxFuture)
                {
                    maxFuture = future[j];
                    optimalIndex = j;
                }
            }
            frames[optimalIndex] = page;
            pageFaultsOptimal++;
        }
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaultsFIFO);
    printf("Total Page Faults (LRU): %d\n", pageFaultsLRU);
    printf("Total Page Faults (Optimal): %d\n", pageFaultsOptimal);
    return 0;
}
