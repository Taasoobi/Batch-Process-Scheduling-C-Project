#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

//Batch processes[MAX_PROCESSES];
int size;
Batch *bacharr;
Batch *fifoarr;
Batch *sjfarr;
Batch *srtarr;

void params(){
    int i;

    printf("Enter total number of processes: ");
    scanf("%d", &size);
    bacharr = (Batch*)malloc(sizeof(Batch)*size);

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

int main(){
    int inp;
    bool menu = true;

    while (menu == true)
    {
        printf("\n Batch Scheduling");
        printf("\n -----------------------------");
        printf("\n 1) Enter Parameters");
        printf("\n 2) Schedule Process with FIFO Algorithm.");
        printf("\n 3) Schedule Process with SJF Algoritm.");
        printf("\n 4) Schedule Process with SRT Algorithm.");
        printf("\n 5) Quit and Free Memory.");
        printf("\n Enter Selection: ");
        scanf("%d", &inp);

        if (inp == 1)
        {
            params();//Test Input: 1 3 1 0 6 2 1 3 3 3 2 3
        } else if (inp == 2){
            fifo();//func 2
        } else if (inp == 3){
            sjf();//func 3
        } else if (inp == 4){
            //func 4
            scheduleSRT(bacharr, size);
        } else if (inp == 5){
            printf("\n Memory Freed and Program Quitted Successfully.");
            menu = false;
        } else {
            printf("\n Error! Enter a number 1-5");
        }
    
    }

    free(bacharr);
    return 0;
}