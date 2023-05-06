#ifndef READY_Q
#define READY_Q
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"

/*
    ready queue is circular queue based on process pointer array.
    This ready queue is for nonpreemptive FCFS scheduling. 
*/
typedef struct ready_Q
{
    process_ptr ready_circular_q[PROC_NUM];
    int start_idx;
    int end_idx;
    int size;
}RQ;

typedef RQ* rq_ptr;

/*
    insert process to ready queue
    return 1 if ready queue already full.
*/
int insert_to_ready_Q(rq_ptr read_q, process_ptr process){
    if(read_q->size == PROC_NUM){
        printf("[ERROR] The ready queue is full.\n");
        return 1;
    }
    read_q->ready_circular_q[read_q->end_idx] = process;
    read_q->end_idx = (read_q->end_idx + 1)%PROC_NUM;
    read_q->size++;
    return 0;
}

/*
    dequeue process from ready queue
    return dequeued process's address
*/
process_ptr dequeue_from_ready_Q(rq_ptr ready_q){
    if(ready_q->size == 0){
        printf("[ERROR] queue underflow.\n");
        return;
    }
    process_ptr dequeued_process = (ready_q->ready_circular_q)[ready_q->start_idx];
    ready_q->start_idx = (ready_q->start_idx + 1)%PROC_NUM;
    ready_q->size--;
    return dequeued_process;
}

rq_ptr init_rq(rq_ptr rq_addr){
    rq_addr = (rq_ptr)malloc(sizeof(RQ));
    for(int i=0; i<PROC_NUM; i++){
        rq_addr->ready_circular_q[i] = 0;
    }
    rq_addr->start_idx = 0;
    rq_addr->end_idx = 0;
    rq_addr->size = 0;
    return rq_addr;
}






#endif