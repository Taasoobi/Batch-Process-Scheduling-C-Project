#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Global Variables
struct batchItem{
    int id;
    int arrival;
    int total;
};
typedef struct batchItem bach;


void params(){
    int size;
    printf("\n Enter total number of processes: ");
    scanf("%d", &size);

    bach *bacharr = (bach*)malloc(sizeof(bach)*size);

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
            params();//Test Input: 1 3 1 0 6 2 1 3 3 3 2
        } else if (inp == 2){
            //func 2
        } else if (inp == 3){
            //func 3
        } else if (inp == 4){
            //func 4
        } else if (inp == 5){
            printf("\n Memory Freed and Program Quitted Successfully.");
            menu = false;
        } else {
            printf("\n Error! Enter a number 1-5");
        }
    
    }

    return 0;
}