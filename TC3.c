#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./cpu_scheduler_module.h"

int main(int argc, char* argv){
    srand(time(NULL));
    cpu_scheduler_ptr cpu_scheduler = Config(cpu_scheduler);
    cpu_scheduler = Create_process(cpu_scheduler);
    printf("test dequeue\n");
    for(int i=0; i< PROC_NUM; i++){
        process_ptr dequeued_process = HeapExtractMax(cpu_scheduler->job_queue);
        insert_to_ready_Q(cpu_scheduler->ready_queue, dequeued_process);
    }
    
    for(int i=0; i< PROC_NUM; i++){
        process_ptr dequeued_process = dequeue_from_ready_Q(cpu_scheduler->ready_queue);
        printf("P%d arrival, priority: %d, %d\n", dequeued_process->pid, dequeued_process->arrival_time, dequeued_process->priority);
    }
    distroy_scheduler(cpu_scheduler);
    
}