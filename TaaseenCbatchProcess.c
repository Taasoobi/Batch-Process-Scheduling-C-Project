#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



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
        scanf("%d", &inp);

        if (inp == 1)
        {
            //Enter Param Function
        }
        

    }
    

    return 0;
}