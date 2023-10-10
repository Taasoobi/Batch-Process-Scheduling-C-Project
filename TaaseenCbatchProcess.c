#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct{
    int id;
    int arrival;
    int total_cycles;
    int total_remaining;
    int done;
    int start;
    int already_started;
    int end;
    int turnaround;
}Batch;

//Global Variables and Pointers
int size;
Batch *bacharr;
Batch *fifoarr;
Batch *sjfarr;
Batch *srtarr;

void params(){
    printf("Enter total number of rocsss: ");
    scanf("%d", &size);

    //allocate memory for all arrays
    bacharr = (Batch*)malloc(sizeof(Batch)*size);
    fifoarr = (Batch*)malloc(sizeof(Batch)*size);
    sjfarr = (Batch*)malloc(sizeof(Batch)*size);
    srtarr = (Batch*)malloc(sizeof(Batch)*size);

    for (int i = 0; i < size; i++) {
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
    printf("\n");
    printf("\n__________________________________________________");
    printf("\nParameters");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf(" %2d    %2d       %2d\n",
        bacharr[i].id, bacharr[i].arrival,
        bacharr[i].total_cycles);
    }
    printf("\n__________________________________________________");
}

void fifo(){
    printf("\nFIFO: ");
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
    printTable(fifoarr, size);
}

void sjf(){
    printf("\nSJF: ");
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

    printTable(sjfarr, size);    
}

void srt(){
    printf("\nSRT: ");
    int time = 0;
    int shortest;
    int i;

    while (1){
        shortest = -1;
        for (i = 0; i < size; i++) {
            if (srtarr[i].done == 0 && srtarr[i].arrival <= time){
                if (shortest == -1 || srtarr[i].total_remaining < srtarr[shortest].total_remaining) {
                    shortest = i;
                }
            }
        }
        if (shortest == -1){
            time++;
            continue;
        }
        if (srtarr[shortest].already_started == 0){
            srtarr[shortest].start = time;
            srtarr[shortest].already_started = 1;
        }

        srtarr[shortest].total_remaining--;
        time++;

        if (srtarr[shortest].total_remaining == 0){
            srtarr[shortest].end = time;
            srtarr[shortest].turnaround = srtarr[shortest].end - srtarr[shortest].arrival;
            srtarr[shortest].done = 1;
        }
        if (srtCheck(srtarr, size)){
            break;
            }
    }

    printTable(srtarr, size);    
}

//checks if each index is done in SRT Algorithm, Returns 1 to end while loop in SRT function
int srtCheck(Batch *processes, int size){
    for (int i = 0; i < size; i++) {
        if (processes[i].done == 0)
            return 0;
    }
    return 1;
}

void printTable(Batch *process, int size) {
    //printf("\n");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf(" %2d    %2d       %2d     %2d      %2d      %2d\n",
        process[i].id, process[i].arrival,
        process[i].total_cycles, process[i].start,
        process[i].end, process[i].turnaround);
    }
    printf("\n__________________________________________________");
}

int main(){
    int inp;
    bool menu = true;
    while (menu == true)
    {
        printf("\n      Batch Scheduling");
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
            srt();//func 4
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