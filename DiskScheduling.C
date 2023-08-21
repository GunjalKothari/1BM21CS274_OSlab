#include <stdio.h>
#include <stdlib.h>
// Function to calculate total seek time for FCFS algorithm
int fcfs(int head, int queue[], int n)
{
    int seekTime = 0;
    for (int i = 0; i < n; i++)
    {
        seekTime += abs(head - queue[i]);
        head = queue[i];
    }
    return seekTime;
}
// Function to calculate total seek time for SCAN algorithm
int scan(int head, int queue[], int n, int maxCylinder)
{
    int seekTime = 0;
    int direction = 1; // 1 for moving towards higher cylinders, -1 for lower cylinders
    int idx = 0;
    while (idx < n)
        {
        seekTime += abs(head - queue[idx]);
        head = queue[idx];
        if (head == maxCylinder)
        {
            direction = -1;
        } else if (head == 0)
        {
            direction = 1;
        }
        head += direction;
        idx++;
    }
    return seekTime;
}
// Function to calculate total seek time for C-SCAN algorithm
int cscan(int head, int queue[], int n, int maxCylinder)
{
    int seekTime = 0;
    int idx = 0;
    while (idx < n)
    {
        seekTime += abs(head - queue[idx]);
        head = queue[idx];
        if (head == maxCylinder)
        {
            seekTime += abs(head);
            head = 0;
        }
        idx++;
    }
    return seekTime;
}
// Function to calculate total seek time for SSTF algorithm
// Function to calculate total seek time for SSTF algorithm
int sstf(int head, int queue[], int n, int maxCylinder)
 {
    int seekTime = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < n; i++)
        {
        int minDist = maxCylinder; // Corrected here
        int idx = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && abs(head - queue[j]) < minDist)
            {
                minDist = abs(head - queue[j]);
                idx = j;
            }
        }
        if (idx != -1)
        {
            seekTime += minDist;
            head = queue[idx];
            visited[idx] = 1;
        }
    }
    return seekTime;
}
// Function to calculate total seek time for LOOK algorithm
int look(int head, int queue[], int n, int maxCylinder)
{
    int seekTime = 0;
    int direction = 1; // 1 for moving towards higher cylinders, -1 for lower cylinders
    int idx = 0;
    while (idx < n)
        {
        seekTime += abs(head - queue[idx]);
        head = queue[idx];
        if (head == maxCylinder)
        {
            direction = -1;
        } else if (head == 0)
        {
            direction = 1;
        }
        if (idx < n - 1)
        {
            if ((direction == 1 && queue[idx + 1] > head) || (direction == -1 && queue[idx + 1] < head))
            {
                idx++;
            }
        } else
        {
            idx++;
        }
        head += direction;
    }
    return seekTime;
}
// Function to calculate total seek time for C-LOOK algorithm
int clook(int head, int queue[], int n)
 {
    int seekTime = 0;
    int idx = 0;
    while (idx < n)
    {
        seekTime += abs(head - queue[idx]);
        head = queue[idx];
        idx++;
    }
    return seekTime;
}
int main()
{
    int n; // Number of disk I/O requests
    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &n);
    int queue[n]; // Array to store disk I/O requests
    printf("Enter the disk I/O requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &queue[i]);
    }
    int head; // Current position of the disk head
    printf("Enter the current position of the disk head: ");
    scanf("%d", &head);
    int maxCylinder; // Maximum cylinder value of the disk
    printf("Enter the maximum cylinder value of the disk: ");
    scanf("%d", &maxCylinder);
    int choice; // User's choice for algorithm
    printf("Choose the disk scheduling algorithm: \n");
    printf("1. FCFS \n 2. SCAN\n 3. C-SCAN\n 4. SSTF\n 5. LOOK\n 6. C-LOOK\n");
    scanf("%d", &choice);
    int totalSeekTime = 0;
    switch (choice)
    {
        case 1:
            totalSeekTime = fcfs(head, queue, n);
            break;
        case 2:
            totalSeekTime = scan(head, queue, n, maxCylinder);
            break;
        case 3:
            totalSeekTime = cscan(head, queue, n, maxCylinder);
            break;
         case 4:
            totalSeekTime = sstf(head, queue, n, maxCylinder); // Pass maxCylinder here
            break;
        case 5:
            totalSeekTime = look(head, queue, n, maxCylinder);
            break;
        case 6:
            totalSeekTime = clook(head, queue, n);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }
    printf("Total Seek Time: %d\n", totalSeekTime);
    return 0;
}
