#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"
/*
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
*/
int main(int argc, char* argv){
    srand(time(NULL));

    process_ptr test_process[10];

    for(int i=0; i<PROC_NUM; i++){
        test_process[i] = process_init(test_process[i], i);
    }
    
    for(int i=0; i<PROC_NUM; i++){
        printf("process %d\n", i);
        printf("process pid: %d\n", test_process[i]->pid);
        printf("process arrival_time: %d\n", test_process[i]->arrival_time);
        printf("process cpu_burst_time: %d\n", test_process[i]->cpu_burst_time);
        printf("process io_start_time: %d\n", test_process[i]->io_start_time);
        printf("process io_burst_time: %d\n", test_process[i]->io_burst_time);
        printf("process priority: %d\n", test_process[i]->priority);
        printf("process remainint_cpu_time: %d\n", test_process[i]->remaining_cpu_time);
        printf("process remaining_io_time: %d\n", test_process[i]->remaining_io_time);
        printf("process is_end: %d\n", test_process[i]->is_end);
        printf("\n");
    }
}