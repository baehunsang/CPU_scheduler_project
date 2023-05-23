#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./cpu_scheduler_module.h"

int main(int argc, char* argv){
    srand(time(NULL));
    cpu_scheduler_ptr cpu_scheduler = Config(cpu_scheduler);
    cpu_scheduler = Create_process(cpu_scheduler);

    for(int i=0; i<PROC_NUM; i++){
        printf("process %d\n", cpu_scheduler->trace_process[i]->pid);
        printf("process pid: %d\n", cpu_scheduler->trace_process[i]->pid);
        printf("process arrival_time: %d\n", cpu_scheduler->trace_process[i]->arrival_time);
        printf("process cpu_burst_time: %d\n", cpu_scheduler->trace_process[i]->cpu_burst_time);
        printf("process io_start_time: %d\n", cpu_scheduler->trace_process[i]->io_start_time);
        printf("process io_burst_time: %d\n", cpu_scheduler->trace_process[i]->io_burst_time);
        printf("process priority: %d\n", cpu_scheduler->trace_process[i]->priority);
        printf("process remainint_cpu_time: %d\n", cpu_scheduler->trace_process[i]->remaining_cpu_time);
        printf("process remaining_io_time: %d\n", cpu_scheduler->trace_process[i]->remaining_io_time);
        printf("process is_end: %d\n", cpu_scheduler->trace_process[i]->is_end);
        printf("\n");
    }
    printf("\n\nFCFS\n");
    Schedule(cpu_scheduler, "FCFS");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);

    reset_process(cpu_scheduler);
    printf("\n\n");
    printf("Nonpreemptive SJF\n");
    Schedule(cpu_scheduler, "NP_SJF");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);
    
    reset_process(cpu_scheduler);
    printf("\n\n");
    printf("Nonpreemptive Priority\n");
    Schedule(cpu_scheduler, "NP_Priority");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);

    reset_process(cpu_scheduler);
    printf("\n\n");
    printf("Preemptive SJF\n");
    Schedule(cpu_scheduler, "P_SJF");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);
    
    reset_process(cpu_scheduler);
    printf("\n\n");
    printf("Preemptive Priority\n");
    Schedule(cpu_scheduler, "P_Priority");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);

    reset_process(cpu_scheduler);
    printf("\n\n");
    printf("Round Robin\n");
    Schedule(cpu_scheduler, "RR");
    print_log(cpu_scheduler->log);
    Evaluation(cpu_scheduler);
    distroy_scheduler(cpu_scheduler);
}