#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
} Process;

void enterParameters(Process processes[], int num_processes);
void scheduleFIFO(Process processes[], int num_processes);
void scheduleSJF(Process processes[], int num_processes);
void scheduleSRT(Process processes[], int num_processes);
void printTable(Process processes[], int num_processes);
void freeMemory(Process processes[], int num_processes);

int main() {
    Process processes[MAX_PROCESSES];
    int num_processes = 0;
    int choice;

    do {
        printf("Batch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        printf("\nEnter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterParameters(processes, num_processes);
                break;
            case 2:
                scheduleFIFO(processes, num_processes);
                break;
            case 3:
                scheduleSJF(processes, num_processes);
                break;
            case 4:
                scheduleSRT(processes, num_processes);
                break;
            case 5:
                freeMemory(processes, num_processes);
                printf("Quitting program\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    } while (choice != 5);

    return 0;
}

void enterParameters(Process processes[], int num_processes) {
    int i;

    printf("Enter total number of processes: ");
    scanf("%d", &num_processes);

    for (i = 0; i < num_processes; i++) {
        printf("Enter process id: ");
        scanf("%d", &processes[i].id);
        printf("Enter arrival cycle for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival);
        printf("Enter total cycles for process %d: ", processes[i].id);
        scanf("%d", &processes[i].total_cpu);

        processes[i].total_remaining = processes[i].total_cpu;
        processes[i].done = 0;
        processes[i].start_time = 0;
        processes[i].already_started = 0;
        processes[i].end_time = 0;
        processes[i].turnaround_time = 0;
    }
}

void scheduleFIFO(Process processes[], int num_processes) {
    int current_time = 0;
    int i;

    for (i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival)
            current_time = processes[i].arrival;

        processes[i].start_time = current_time;
        processes[i].end_time = current_time + processes[i].total_cpu;
        processes[i].turnaround_time = processes[i].end_time - processes[i].arrival;
        current_time = processes[i].end_time;
        processes[i].done = 1;
    }

    printTable(processes, num_processes);
}

void scheduleSJF(Process processes[], int num_processes) {
    int current_time = 0;
    int shortest_index;
    int i, j;

    for (i = 0; i < num_processes; i++) {
        shortest_index = -1;
        for (j = 0; j < num_processes; j++) {
            if (processes[j].done == 0 && processes[j].arrival <= current_time) {
                if (shortest_index == -1 || processes[j].total_cpu < processes[shortest_index].total_cpu) {
                    shortest_index = j;
                }
            }
        }

        if (shortest_index == -1) {
            current_time++;
            i--;
            continue;
        }

        processes[shortest_index].start_time = current_time;
        processes[shortest_index].end_time = current_time + processes[shortest_index].total_cpu;
        processes[shortest_index].turnaround_time = processes[shortest_index].end_time - processes[shortest_index].arrival;
        current_time = processes[shortest_index].end_time;
        processes[shortest_index].done = 1;
    }

    printTable(processes, num_processes);
}

void scheduleSRT(Process processes[], int num_processes) {
    int current_time = 0;
    int shortest_index;
    int i;

    while (1) {
        shortest_index = -1;
        for (i = 0; i < num_processes; i++) {
            if (processes[i].done == 0 && processes[i].arrival <= current_time) {
                if (shortest_index == -1 || processes[i].total_remaining < processes[shortest_index].total_remaining) {
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        if (processes[shortest_index].already_started == 0) {
            processes[shortest_index].start_time = current_time;
            processes[shortest_index].already_started = 1;
        }

        processes[shortest_index].total_remaining--;
        current_time++;

        if (processes[shortest_index].total_remaining == 0) {
            processes[shortest_index].end_time = current_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].end_time - processes[shortest_index].arrival;
            processes[shortest_index].done = 1;
        }

        if (checkAllDone(processes, num_processes))
            break;
    }

    printTable(processes, num_processes);
}

void printTable(Process processes[], int num_processes) {
    int i;

    printf("\nID Arrival Total Start End Turnaround\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < num_processes; i++) {
        printf("%d %d %d %d %d %d\n", processes[i].id, processes[i].arrival, processes[i].total_cpu,
               processes[i].start_time, processes[i].end_time, processes[i].turnaround_time);
    }
}

void freeMemory(Process processes[], int num_processes) {
    // No memory to free in this case
}

int checkAllDone(Process processes[], int num_processes) {
    int i;

    for (i = 0; i < num_processes; i++) {
        if (processes[i].done == 0)
            return 0;
    }

    return 1;
}