#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int total_processes = 0;
typedef struct process
{
    int id;
    int arrival;
    int total_cpu;
    int start;
    int end;
    int turnaround;
} process;

process *table = NULL;

void release()
{
    if (total_processes > 0)
    {
        total_processes = 0;
        free(table);
    }
} // release()

void enter()
{
    int i;
    release();
    printf("Enter total number of processes: ");
    scanf("%d", &total_processes);
    if (total_processes <= 0)
    {
        printf("Invalid number of processe. \n");
        return;
    }

    table = (process *)malloc(total_processes * sizeof(process));
    for (i = 0; i < total_processes; i++)
    {
        int arrival = -1;
        int total_cpu = -1;
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &arrival);
        if (arrival < 0)
        {
            printf("Invalid arrival time. \n");
            release();
            return;
        }

        printf("Enter total cpu time for process %d: ", i);
        scanf("%d", &total_cpu);
        if (total_cpu < 0)
        {
            printf("Invalid total CPU time. \n");
            release();
            return;
        }

        table[i].id = i;
        table[i].arrival = arrival;
        table[i].total_cpu = total_cpu;
        table[i].start = -1;
        table[i].end = -1;
        table[i].turnaround = -1;
    }

} // enter()

void sort_table()
{
    int i, j;
    for (i = 0; i < total_processes - 1; i++)
    {
        for (j = i + 1; j < total_processes; j++)
        {
            if (table[i].arrival > table[j].arrival)
            {
                process temp = table[i];
                table[i] = table[j];
                table[j] = temp;
            }
        }
    }
} // sort_table()

void print_table()
{
    printf("ID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
    printf("--------------------------------------------------\n");
    int i;
    for (i = 0; i < total_processes; i++)
    {
        printf("%d\t", table[i].id);
        printf("%d\t", table[i].arrival);
        printf("%d\t", table[i].total_cpu);
        printf("%d\t", table[i].start);
        printf("%d\t", table[i].end);
        printf("%d\n", table[i].turnaround);
    }

} // print_table()

void schedule(int algo)
{
    int i, j;
    if (total_processes <= 0)
    {
        printf("Invalid number of processe. \n");
        return;
    }

    // sort the table
    sort_table();
    // iteretae through the table
    for (i = 0; i < total_processes; i++)
    {
        if (i == 0)
        {
            table[i].start = table[i].arrival;
        }
        else
        {
            // check for scheduling conflict
            if (table[i].arrival >= table[i - 1].end)
            {
                table[i].start = table[i].arrival;
            }
            else
            {
                if (algo == 1)
                {
                    for (j = i + 1; j < total_processes &&
                                    table[j].arrival < table[i - 1].end;
                         j++)
                    {
                        if (table[i].total_cpu > table[j].total_cpu)
                        {
                            process temp = table[i];
                            table[i] = table[j];
                            table[j] = temp;
                        }
                    }
                }
                table[i].start = table[i - 1].end;
            }
        }
        // calculate end time and turnaround
        table[i].end = table[i].start + table[i].total_cpu;
        table[i].turnaround = table[i].end - table[i].arrival;
    }
    // print the table
    print_table();
} // schedule()

int main()
{

    int option = 0;

    while (option != 4)
    {

        // used for program safety and avoid infinite loop

        option = 4;

        printf("Batch Schedulimg\n");

        printf("---------------------------------\n");

        printf("1) Enter Parameters\n");

        printf("2) Schedule processes with FIFO algorithm\n");

        printf("3) Schedule processes with SJF algorithm\n");

        printf("4) Quit program and free memory\n");

        printf("\n");

        printf("Enter Selection: ");

        scanf("%d", &option);

        printf("\n");

        switch (option)
        {

        case 1:

            enter();

            break;

        case 2:

            schedule(0);

            break;

        case 3:

            schedule(1);

            break;

        case 4:

            printf("Goodbye");

            release();

            break;

        default:

            printf("Invalid option, try again. \n");
        }

        printf("\n");
    }

    return 0;
}