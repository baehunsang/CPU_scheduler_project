#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"
#include "./definition_job_queue.h"

typedef struct cpu_scheduler
{
    process_ptr trace_process[PROC_NUM];
    jq_ptr job_queue;
}cpu_scheduler;

typedef cpu_scheduler* cpu_scheduler_ptr;

/*
    initialize system (job, ready, waiting queue)
*/
cpu_scheduler_ptr Config(cpu_scheduler_ptr cpu_scheduler_addr){
    cpu_scheduler_addr = (cpu_scheduler_ptr)malloc(sizeof(cpu_scheduler));
    cpu_scheduler_addr->job_queue = init_jq(cpu_scheduler_addr->job_queue);
    return cpu_scheduler_addr;
}

/*
    create and insert processes
*/
cpu_scheduler_ptr Create_process(cpu_scheduler_ptr cpu_scheduler_addr){
    for(int i=0; i<PROC_NUM; i++){
        cpu_scheduler_addr->trace_process[i] = process_init(cpu_scheduler_addr->trace_process[i], i);
        Insert(cpu_scheduler_addr->job_queue, cpu_scheduler_addr->trace_process[i]);
    }
    return cpu_scheduler_addr;
}

void distroy_scheduler(cpu_scheduler_ptr cpu_scheduler_addr){
    for(int i=0; i< PROC_NUM; i++){
        free(cpu_scheduler_addr->trace_process[i]);
    }
    free(cpu_scheduler_addr->job_queue);
    free(cpu_scheduler_addr);
}
