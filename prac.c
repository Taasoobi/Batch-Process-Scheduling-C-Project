#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int arrival;
    int total_cycles;
    int total_remaining;
    int done;
    int start;
    int already_started;
    int end;
    int turnaround;
} Batch;

Batch processes[MAX_PROCESSES];
int size;

void enterParameters(/*Process processes[], int size*/) {
    int i;

    printf("Enter total number of processes: ");
    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        printf("Enter process id: ");
        scanf("%d", &processes[i].id);
        printf("Enter arrival cycle for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival);
        printf("Enter total cycles for process %d: ", processes[i].id);
        scanf("%d", &processes[i].total_cycles);

        processes[i].total_remaining = processes[i].total_cycles;
        processes[i].done = 0;
        processes[i].start = 0;
        processes[i].already_started = 0;
        processes[i].end = 0;
        processes[i].turnaround = 0;}
}

void scheduleFIFO(Batch processes[], int size) {
    int current_time = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (current_time < processes[i].arrival)
            current_time = processes[i].arrival;

        processes[i].start = current_time;
        processes[i].end = current_time + processes[i].total_cycles;
        processes[i].turnaround = processes[i].end - processes[i].arrival;
        current_time = processes[i].end;
        processes[i].done = 1;
    }

    printTable(processes, size);
}

void scheduleSJF(Batch processes[], int size) {
    int current_time = 0;
    int shortest_index;
    int i, j;

    for (i = 0; i < size; i++) {
        shortest_index = -1;
        for (j = 0; j < size; j++) {
            if (processes[j].done == 0 && processes[j].arrival <= current_time) {
                if (shortest_index == -1 || processes[j].total_cycles < processes[shortest_index].total_cycles) {
                    shortest_index = j;
                }
            }
        }

        if (shortest_index == -1) {
            current_time++;
            i--;
            continue;
        }

        processes[shortest_index].start = current_time;
        processes[shortest_index].end = current_time + processes[shortest_index].total_cycles;
        processes[shortest_index].turnaround = processes[shortest_index].end - processes[shortest_index].arrival;
        current_time = processes[shortest_index].end;
        processes[shortest_index].done = 1;
    }

    printTable(processes, size);
}

void scheduleSRT(Batch processes[], int size) {
    int current_time = 0;
    int shortest_index;
    int i;

    while (1) {
        shortest_index = -1;
        for (i = 0; i < size; i++) {
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
            processes[shortest_index].start = current_time;
            processes[shortest_index].already_started = 1;
        }

        processes[shortest_index].total_remaining--;
        current_time++;

        if (processes[shortest_index].total_remaining == 0) {
            processes[shortest_index].end = current_time;
            processes[shortest_index].turnaround = processes[shortest_index].end - processes[shortest_index].arrival;
            processes[shortest_index].done = 1;
        }

        if (checkAllDone(processes, size))
            break;
    }

    printTable(processes, size);
}

void printTable(Batch processes[], int size) {
    int i;

    printf("\nID Arrival Total Start End Turnaround\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < size; i++) {
        printf("%2d  %2d     %2d     %2d     %2d     %2d\n", processes[i].id, processes[i].arrival, processes[i].total_cycles,
               processes[i].start, processes[i].end, processes[i].turnaround);
    }
}


int checkAllDone(Batch processes[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (processes[i].done == 0)
            return 0;
    }
    return 1;
}

int main() {
    //Process processes[MAX_PROCESSES];
    //int size = 0;
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

        switch (choice) { //1 3 1 0 6 2 1 3 3 3 2
            case 1:
                enterParameters();
                break;
            case 2:
                scheduleFIFO(processes, size);
                break;
            case 3:
                scheduleSJF(processes, size);
                break;
            case 4:
                scheduleSRT(processes, size);
                break;
            case 5:
                printf("Quitting program\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    } while (choice != 5);

    return 0;
}