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

//Batch bacharr[MAX_bacharr];
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
    fifoarr = (Batch*)malloc(sizeof(Batch)*size);
    sjfarr = (Batch*)malloc(sizeof(Batch)*size);
    srtarr = (Batch*)malloc(sizeof(Batch)*size);

    for (i = 0; i < size; i++) {
        printf("Enter process id: ");
        scanf("%d", &bacharr[i].id);
        printf("Enter arrival cycle for process %d: ", bacharr[i].id);
        scanf("%d", &bacharr[i].arrival);
        printf("Enter total cycles for process %d: ", bacharr[i].id);
        scanf("%d", &bacharr[i].total_cycles);

        bacharr[i].total_remaining = bacharr[i].total_cycles;
        bacharr[i].done = 0;
        bacharr[i].start = 0;
        bacharr[i].already_started = 0;
        bacharr[i].end = 0;
        bacharr[i].turnaround = 0;

        //allocate data in Fifo Array
        fifoarr[i].id = bacharr[i].id;
        fifoarr[i].arrival = bacharr[i].arrival;
        fifoarr[i].total_cycles = bacharr[i].total_cycles;
        fifoarr[i].total_remaining = bacharr[i].total_cycles;
        fifoarr[i].done = 0;
        fifoarr[i].start = 0;
        fifoarr[i].already_started = 0;
        fifoarr[i].end = 0;
        fifoarr[i].turnaround = 0;

        //allocate data in Sjf Array
        sjfarr[i].id = bacharr[i].id;
        sjfarr[i].arrival = bacharr[i].arrival;
        sjfarr[i].total_cycles = bacharr[i].total_cycles;
        sjfarr[i].total_remaining = bacharr[i].total_cycles;
        sjfarr[i].done = 0;
        sjfarr[i].start = 0;
        sjfarr[i].already_started = 0;
        sjfarr[i].end = 0;
        sjfarr[i].turnaround = 0;

        //allocate data in Srt Array
        srtarr[i].id = bacharr[i].id;
        srtarr[i].arrival = bacharr[i].arrival;
        srtarr[i].total_cycles = bacharr[i].total_cycles;
        srtarr[i].total_remaining = bacharr[i].total_cycles;
        srtarr[i].done = 0;
        srtarr[i].start = 0;
        srtarr[i].already_started = 0;
        srtarr[i].end = 0;
        srtarr[i].turnaround = 0;      

    }
}

void fifo(){
    //fifoarr = (batch*)malloc(sizeof(batch)*size);
    printf("\n FIFO: ");
    //First in First out
    fifoarr[0].start = bacharr[0].arrival;
    fifoarr[0].end = bacharr[0].total_cycles;
    fifoarr[0].turnaround = fifoarr[0].end - bacharr[0].arrival;
    int newStart = fifoarr[0].end;
    
    for (int i = 1; i < size; i++)
    {
        fifoarr[i].start = newStart;
        fifoarr[i].end = fifoarr[i].start + bacharr[i].total_cycles;
        newStart = fifoarr[i].end;//for next iteration
        fifoarr[i].turnaround = fifoarr[i].end - bacharr[i].arrival;
    }
    
    printf("\n");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        printf("\n %2d    %2d       %2d     %2d      %2d      %2d", bacharr[i].id, bacharr[i].arrival, bacharr[i].total_cycles, fifoarr[i].start, fifoarr[i].end, fifoarr[i].turnaround);
    }//            id     arrival   total   start   end    turna
    printf("\n\n");

}

void sjf(){
    int time = 0;
    int shortest;
    int i, j;

    for (i = 0; i < size; i++) {
        shortest = -1;
        for (j = 0; j < size; j++) {
            if (sjfarr[j].done == 0 && sjfarr[j].arrival <= time) {
                if (shortest == -1 || sjfarr[j].total_cycles < sjfarr[shortest].total_cycles) {
                    shortest = j;
                }
            }
        }

        if (shortest == -1) {
            time++;
            i--;
            continue;
        }

        sjfarr[shortest].start = time;
        sjfarr[shortest].end = time + sjfarr[shortest].total_cycles;
        sjfarr[shortest].turnaround = sjfarr[shortest].end - sjfarr[shortest].arrival;
        time = sjfarr[shortest].end;
        sjfarr[shortest].done = 1;
    }

    //printTable(sjfarr, size);
    printf("\nID Arrival Total Start End Turnaround\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%2d  %2d     %2d     %2d     %2d     %2d\n", sjfarr[i].id, sjfarr[i].arrival, sjfarr[i].total_cycles,
               sjfarr[i].start, sjfarr[i].end, sjfarr[i].turnaround);
    }    
}

void printTable(Batch *processes, int size) {
    int i;

    printf("\nID Arrival Total Start End Turnaround\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < size; i++) {
        printf("%2d  %2d     %2d     %2d     %2d     %2d\n", processes[i].id, processes[i].arrival, processes[i].total_cycles,
               processes[i].start, processes[i].end, processes[i].turnaround);
    }
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
            params();//Test Input: 1 3 1 0 6 2 1 3 3 3 2 3    Set 2: 1 3 1 0 6 2 1 3 3 3 2
        } else if (inp == 2){
            fifo();//func 2
        } else if (inp == 3){
            sjf();//func 3
        } else if (inp == 4){
            //func 4
            //srt(srtarr, size);
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