#include <stdio.h>
#define MAX_TASKS 10

typedef struct {
    int period;
    int execution_time;
} Task;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int hyperperiod(Task tasks[], int num_tasks) {
    int i, hp = tasks[0].period;

    for (i = 1; i < num_tasks; i++) {
        hp = lcm(hp, tasks[i].period);
    }

    return hp;
}

int main() {
    Task tasks[MAX_TASKS];
    int num_tasks, i;

    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    printf("Enter the period and execution time of each task:\n");
    for (i = 0; i < num_tasks; i++) {
        printf("Task %d:\n", i + 1);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
    }

    int hp = hyperperiod(tasks, num_tasks);
    printf("Hyperperiod: %d\n", hp);

    // Calculate the utilization factor
    double utilization = 0.0;
    for (i = 0; i < num_tasks; i++) {
        utilization += (double)(tasks[i].execution_time) / (double)(tasks[i].period);
    }

    printf("Total Utilization: %f\n", utilization);

    if (utilization <= 1) {
        printf("The system is schedulable under Rate Monotonic Scheduling.\n");
    } else {
        printf("The system is not schedulable under Rate Monotonic Scheduling.\n");
    }

    return 0;
}
