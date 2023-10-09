#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Global Variables
int size;
struct batchItem{
    int id;
    int arrival;
    int total;
    int remaining;
    int done;
    int start;
    int already_started;
    int end;
    int turnaround;
}; //}*table = NULL;
//typedef struct node table_type;
typedef struct batchItem batch;

batch *bacharr;
batch *fifoarr;
batch *sjfarr;
batch *srtarr;
batch *shorti;

void params(){
    //int size;
    printf("\n Enter total number of processes: ");
    scanf("%d", &size);

    bacharr = (batch*)malloc(sizeof(batch)*size);

    int idin;
    int arrin;
    int totalin;
    for (int i = 0; i < size; i++)
    {
        printf("\n Enter process id: ");
        scanf("%d", &idin);
        bacharr[i].id = idin;
        printf("\n Enter arrival cycle for process P[%d]: ", idin);
        scanf("%d", &arrin);
        bacharr[i].arrival = arrin;
        printf("\n Enter total cycles for process P[%d]: ", idin);
        scanf("%d", &totalin);
        bacharr[i].total = totalin;
    }

    printf("\n");
    printf("\n ID   Arrival   Total   Start   End   Turnaround");
    printf("\n ------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        printf("\n %d       %d        %d", bacharr[i].id, bacharr[i].arrival, bacharr[i].total);
    }
    printf("\n\n");
}

void fifo(){
    fifoarr = (batch*)malloc(sizeof(batch)*size);
    printf("\n FIFO: ");
    //First in First out
    fifoarr[0].start = bacharr[0].arrival;
    fifoarr[0].end = bacharr[0].total;
    fifoarr[0].turnaround = fifoarr[0].end - bacharr[0].arrival;
    int newStart = fifoarr[0].end;
    
    for (int i = 1; i < size; i++)
    {
        fifoarr[i].start = newStart;
        fifoarr[i].end = fifoarr[i].start + bacharr[i].total;
        newStart = fifoarr[i].end;//for next iteration
        fifoarr[i].turnaround = fifoarr[i].end - bacharr[i].arrival;
    }
    
    printf("\n");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        printf("\n %2d    %2d       %2d     %2d      %2d      %2d", bacharr[i].id, bacharr[i].arrival, bacharr[i].total, fifoarr[i].start, fifoarr[i].end, fifoarr[i].turnaround);
    }//            id     arrival   total   start   end    turna
    printf("\n\n");

}

void bubbleSort()
{
    int i, j;
    bool swapped;
    int nSize;
    nSize = size-1;
    for (i = 1; i < nSize - 1; i++) { //changed i = 0 -> i=1,
        swapped = false;
        for (j = 1; j < nSize - i - 1; j++) {
            if (shorti[j].total > shorti[j + 1].total) {
                swap(&shorti[j].total, &shorti[j + 1].total);
                swapped = true;
            }
        }
 
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void selectionSort() 
{ 
    int i, j, min_idx; 
    int nSize = size-1;

    // One by one move boundary of 
    // unsorted subarray 
    for (i = 1; i < size - 1; i++) { 
        // Find the minimum element in 
        // unsorted array 
        min_idx = i; 
        for (j = i + 1; j < size; j++) 
            if (shorti[j].total < shorti[min_idx].total) 
                min_idx = j; 
  
        // Swap the found minimum element 
        // with the first element 
        swap(&shorti[min_idx].total, &shorti[i].total);
    } 
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sjf(){
    sjfarr = (batch*)malloc(sizeof(batch)*size);
    //private checking array
    shorti = (batch*)malloc(sizeof(batch)*size);
    batch *sorted = (batch*)malloc(sizeof(batch)*size);
    //SJF = shortest job first (Not preemptive)
    /*    */

    sjfarr[0].start = bacharr[0].arrival;
    sjfarr[0].end = bacharr[0].total;
    sjfarr[0].turnaround = sjfarr[0].end - bacharr[0].arrival;

    int shortest;//shortest total (total cycles)
    shortest = bacharr[1].total;
    shorti[0].total = bacharr[0].total;//was shorti[0].total = shortest; 
    int temp;
    
    for (int i = 1; i < size; i++)
    {
        shorti[i].total = bacharr[i].total;
    }
    
    //bubbleSort();
    selectionSort();
    /*
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (shortest > bacharr[j+1].total)
            {
                shortest = bacharr[j+1].total;
                temp = bacharr[j].total;
                shorti[i].total = shortest;
                shorti[i+1].total = temp;
                
            } else {
                shorti[j].total = bacharr[j].total;
            }
            //check[i].total = shortest;
        }
        //shorti[i].total = shortest;
        temp = shortest;
    }*/

    printf("\n");
    printf("\n Shortest Array");
    for (int i = 0; i < size; i++)
    {
        printf("\n %2d", shorti[i].total);
    }
    



        printf("\n");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        printf("\n %2d    %2d       %2d     %2d      %2d      %2d", bacharr[i].id, bacharr[i].arrival, bacharr[i].total, sjfarr[i].start, sjfarr[i].end, sjfarr[i].turnaround);
    }//            id     arrival   total   start   end    turna
    printf("\n\n");
}

void srt(){
    srtarr = (batch*)malloc(sizeof(batch)*size);
    //Shortest Remaining Time (Is Preemptive)
    /*    */
        printf("\n");
    printf("\n ID   Arrival  Total   Start   End     Turnaround");
    printf("\n ------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        printf("\n %2d    %2d       %2d     %2d      %2d      %2d", bacharr[i].id, bacharr[i].arrival, bacharr[i].total, &fifoarr[i].start, &fifoarr[i].end, &fifoarr[i].turnaround);
    }//            id     arrival   total   start   end    turna
    printf("\n\n");
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