#ifndef PROCESS
#define PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROC_NUM 4
#define MAX_ARRIVAL 5
#define MAX_BURST 5
#define MAX_PRIORITY 10
#define TRUE 1
#define FALSE 0

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
    int io_timer;
    int is_io;
    int is_end;
    int TT;
    int WT;
    int is_run;
    ////////////////////////////
}process;

typedef process* process_ptr;

/*
    Initialize process with random values
    [in]process_addr
    [in]pid

    [out]iniialized process's address
*/
process_ptr process_init(process_ptr process_addr, int pid){
    process_addr = (process_ptr)malloc(sizeof(process));
    process_addr->pid = pid;
    //[0: MAX_ARRIVAL]
    process_addr->arrival_time = (rand() % (MAX_ARRIVAL + 1));
    //[2: MAX_BURST]
    /*
        edge case: what if cpu burst:1, io_start:1 ?
        we don't manage this condition
    */
    process_addr->cpu_burst_time = (rand() % (MAX_BURST - 1)) + 2;
    //[1: cpu_burst - 1]
    process_addr->io_start_time = (rand() % (process_addr->cpu_burst_time - 1)) + 1;
    //[1: MAX_BURST]
    process_addr->io_burst_time = (rand() % MAX_BURST) + 1;
    //[0: MAX_PRIORITY - 1]
    process_addr->priority = (rand() % MAX_PRIORITY);
    process_addr->remaining_cpu_time = process_addr->cpu_burst_time;
    process_addr->remaining_io_time = process_addr->io_burst_time;
    process_addr->io_timer = process_addr->io_start_time;
    process_addr->is_end = FALSE;
    process_addr->is_io = FALSE;
    process_addr->WT = 0;
    process_addr->TT = -process_addr->arrival_time;
    process_addr->is_run = FALSE;
    return process_addr;
}

process_ptr re_process_init(process_ptr process_addr){
    process_addr->remaining_cpu_time = process_addr->cpu_burst_time;
    process_addr->remaining_io_time = process_addr->io_burst_time;
    process_addr->io_timer = process_addr->io_start_time;
    process_addr->is_end = FALSE;
    process_addr->is_io = FALSE;
    process_addr->WT = 0;
    process_addr->TT = -process_addr->arrival_time;
    process_addr->is_run = FALSE;
    return process_addr;
}
#endif
