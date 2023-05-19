#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./process.h"
#include "./definition_job_queue.h"
#include "./definition_ready_Q.h"
#include "./process_log.h"

typedef struct cpu_scheduler
{
    process_ptr trace_process[PROC_NUM];
    jq_ptr job_queue;
    rq_ptr ready_queue;

    process_ptr core;
    process_log_list_ptr log;

}cpu_scheduler;

typedef cpu_scheduler* cpu_scheduler_ptr;

/*
    initialize system (job, ready, log_list)
*/
cpu_scheduler_ptr Config(cpu_scheduler_ptr cpu_scheduler_addr){
    cpu_scheduler_addr = (cpu_scheduler_ptr)malloc(sizeof(cpu_scheduler));
    cpu_scheduler_addr->job_queue = init_jq(cpu_scheduler_addr->job_queue);
    cpu_scheduler_addr->ready_queue = init_rq(cpu_scheduler_addr->ready_queue);
    cpu_scheduler_addr->log = init_log_list(cpu_scheduler_addr->log);
    return cpu_scheduler_addr;
}

/*
    create and insert processes to job queue.
*/
cpu_scheduler_ptr Create_process(cpu_scheduler_ptr cpu_scheduler_addr){
    for(int i=0; i<PROC_NUM; i++){
        cpu_scheduler_addr->trace_process[i] = process_init(cpu_scheduler_addr->trace_process[i], i);
        Insert(cpu_scheduler_addr->job_queue, cpu_scheduler_addr->trace_process[i]);
    }
    return cpu_scheduler_addr;
}

/*
    reset dynamic field in processes
*/
void reset_process(cpu_scheduler_ptr cpu_scheduler_addr){
    //process log should reset
    destroy_log(cpu_scheduler_addr->log);
    cpu_scheduler_addr->log = init_log_list(cpu_scheduler_addr->log);
    
    for(int i=0; i<PROC_NUM; i++){
        cpu_scheduler_addr->trace_process[i] = re_process_init(cpu_scheduler_addr->trace_process[i]);
        Insert(cpu_scheduler_addr->job_queue, cpu_scheduler_addr->trace_process[i]);
    }
    return cpu_scheduler_addr;
}

/*
    if all processes are end then return 1 else return 0
*/
int is_terminal(cpu_scheduler_ptr cpu_scheduler_addr){
    int terminal = TRUE;
    for(int i=0; i< PROC_NUM; i++){
        if(!cpu_scheduler_addr->trace_process[i]->is_end){
            terminal = FALSE;
            break;
        }
    }
    return terminal;
}

void __schedule_fcfs(cpu_scheduler_ptr cpu_scheduler_addr){
    int current_time = 0;
    int start_time = 0;
    //1 while roop represents 1ms
    /*
        while current time is JQ.HeapMax()->arrival time
            1.dequeue process from JQ
            2.insert process into ready Q

        if core is NULL
            1.dequeue process from ready Q
            2.schedule core to process

        if running process's io_timer == 0
            1.change process's is_io field to TRUE
            2. insert process into log_list
            if ready Q's size is not 0
                1.dequeue process from ready Q
                2.schedule core to process
            else
                core = NULL

        if running process's remaining_cpu_burst == 0
            1. insert process into log_list
            2. change process's is_end field to TRUE
        
        if io_process's remaining_io == 0
            1. insert process into ready Q
            2. change process's is_io field to FALSE

        io_process's remaining_io--
        running process's remaining_cpu_burst--
        running process's io_timer--
        
        
    */
    while(!is_terminal(cpu_scheduler_addr)){
        /*
        while current time is JQ.HeapMax()->arrival time
            1.dequeue process from JQ
            2.insert process into ready Q
        */
        while(cpu_scheduler_addr->job_queue->size && current_time == HeapMax(cpu_scheduler_addr->job_queue)->arrival_time){
            process_ptr dequeued_process = HeapExtractMax(cpu_scheduler_addr->job_queue);
            insert_to_ready_Q(cpu_scheduler_addr->ready_queue, dequeued_process);
        }
        /*
        if core is NULL
            1.dequeue process from ready Q
            2.schedule core to process
        */
        if(!cpu_scheduler_addr->core && cpu_scheduler_addr->ready_queue->size){
            cpu_scheduler_addr->core = dequeue_from_ready_Q(cpu_scheduler_addr->ready_queue);
            start_time = current_time;
        }

        /*
        if running process's io_timer == 0
            1.change process's is_io field to TRUE
            2. insert process into log_list
            if ready Q's size is not 0
                1.dequeue process from ready Q
                2.schedule core to process
            else
                core = NULL
        */
        if(cpu_scheduler_addr->core && cpu_scheduler_addr->core->io_timer == 0){
            cpu_scheduler_addr->core->is_io = TRUE;
            cpu_scheduler_addr->core->io_timer = MAX_BURST;
            insert_log(cpu_scheduler_addr->log, cpu_scheduler_addr->core, start_time, current_time);
            if(cpu_scheduler_addr->ready_queue->size){
                cpu_scheduler_addr->core = dequeue_from_ready_Q(cpu_scheduler_addr->ready_queue);
                start_time = current_time;
            }
            else{
                cpu_scheduler_addr->core = NULL;
            }
        }
        /*
        if running process's remaining_cpu_burst == 0
            1. insert process into log_list
            2. change process's is_end field to TRUE
        */
        if(cpu_scheduler_addr->core && cpu_scheduler_addr->core->remaining_cpu_time == 0){
            insert_log(cpu_scheduler_addr->log, cpu_scheduler_addr->core, start_time, current_time);
            cpu_scheduler_addr->core->is_end = TRUE;
            if(cpu_scheduler_addr->ready_queue->size){
                cpu_scheduler_addr->core = dequeue_from_ready_Q(cpu_scheduler_addr->ready_queue);
                start_time = current_time;
            }
            else{
                cpu_scheduler_addr->core = NULL;
            }
        }
        /*
        if io_process's remaining_io == 0
            1. insert process into ready Q
            2. change process's is_io field to FALSE
        */
        for(int i=0; i< PROC_NUM; i++){
            if(cpu_scheduler_addr->trace_process[i]->is_io && !cpu_scheduler_addr->trace_process[i]->remaining_io_time){
                cpu_scheduler_addr->trace_process[i]->is_io = FALSE;
                insert_to_ready_Q(cpu_scheduler_addr->ready_queue, cpu_scheduler_addr->trace_process[i]);
                if(!cpu_scheduler_addr->core && cpu_scheduler_addr->ready_queue->size){
                    cpu_scheduler_addr->core = dequeue_from_ready_Q(cpu_scheduler_addr->ready_queue);
                    start_time = current_time;
                }
            }
        }

        for(int i=0; i< PROC_NUM; i++){
            if(cpu_scheduler_addr->trace_process[i]->is_io){
                cpu_scheduler_addr->trace_process[i]->remaining_io_time--;
            }
        }
        if(cpu_scheduler_addr->core){
            cpu_scheduler_addr->core->remaining_cpu_time--;
            /*
                In this cpu scheduler I/O only accured once. 
            */
            if(cpu_scheduler_addr->core->remaining_io_time){
                cpu_scheduler_addr->core->io_timer--;
            }
        }

        current_time++;
    }
}

void Schedule(cpu_scheduler_ptr cpu_scheduler_addr, char* msg){
    if(!strncmp(msg, "FCFS", 4)){
        __schedule_fcfs(cpu_scheduler_addr);
    }

}

/*
    return allocated memory
*/
void distroy_scheduler(cpu_scheduler_ptr cpu_scheduler_addr){
    for(int i=0; i< PROC_NUM; i++){
        free(cpu_scheduler_addr->trace_process[i]);
    }
    destroy_log(cpu_scheduler_addr->log);
    free(cpu_scheduler_addr->job_queue);
    free(cpu_scheduler_addr->ready_queue);
    free(cpu_scheduler_addr);
}
