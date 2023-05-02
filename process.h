#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROC_NUM 10
#define MAX_ARRIVAL 5
#define MAX_BURST 5
#define MAX_PRIORITY 10

typedef struct process
{   ///////////Project 요구사항///////
    int pid;
    int arrival_time;
    int cpu_burst_time;
    int io_start_time;
    int io_burst_time;
    int priority;
    /////////////////////////////////
    
    //////////추가 속성//////////
    int remaining_cpu_time;
    int remaining_io_time;
    int is_end;
    ////////////////////////////
}process;

typedef process* process_ptr;

process_ptr process_init(process_ptr process, int pid){
    process->pid = pid;
    process->arrival_time = (rand() % MAX_ARRIVAL) + 1;
    process->cpu_burst_time = (rand() % MAX_BURST) + 1;
    process->io_start_time = (rand() % (process->cpu_burst_time)) + 1;
    process->io_burst_time = (rand() % MAX_BURST) + 1;
    process->priority = (rand() % MAX_PRIORITY);
    process->remaining_cpu_time = process->cpu_burst_time;
    process->remaining_io_time = process->io_burst_time;
    process->is_end = 0;
    return process;
}

