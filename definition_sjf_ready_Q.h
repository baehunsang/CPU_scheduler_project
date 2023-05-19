#ifndef SJF_QUEUE
#define SJF_QUEUE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"

typedef struct SJF_RQ
{
    process_ptr job_priority_q[PROC_NUM];
    int size;
}sjf_rq;
typedef sjf_rq* sjf_rq_ptr;
/*
    swap each processes data
    [in]process1's address
    [in]process2's address
*/
void sjf_swap(process_ptr element1, process_ptr element2) {
    process tmp;
    tmp = *element1;
    *element1 = *element2;
    *element2 = tmp;
}

/*
    Get parent node of index value
    [in]index
    [out] patent node's index
*/
int sjf_parent(int index) {
    if (index % 2 == 0) {
        return (index / 2) - 1;
    }
    else {
        return index / 2;
    }
}

/*
    process compare function
    1 if process1's priority is bigger than process2
    else 0
    high priority value has high priority
    sort with arrival time
*/
int sjf_compare(process_ptr process1, process_ptr process2){
    if(process1->remaining_cpu_time < process2->remaining_cpu_time){
        return 1;
    }
    if(process1->remaining_cpu_time == process2->remaining_cpu_time){
        if(process1->priority > process2->priority){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

/*
    Top down heap making function
*/
void sjf_Heapify(sjf_rq_ptr heap, int index) { //Top to Down 
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int largest = index;                   //Making max-heap
    if (leftIndex <= (heap->size) - 1 &&
        sjf_compare(heap->job_priority_q[leftIndex] , heap->job_priority_q[largest])) {              //compare function is needed in here
        largest = leftIndex;
    } // compare left node
    if (rightIndex <= (heap->size) - 1 &&
        sjf_compare(heap->job_priority_q[rightIndex], heap->job_priority_q[largest])) {
        largest = rightIndex;
    }// compare right node
    if (largest != index) {
        sjf_swap(heap->job_priority_q[index], heap->job_priority_q[largest]); // swap
        sjf_Heapify(heap, largest);   // reculsive action, untile last level
    }
}

/*
    Executed each insertion sorting job priority queue.
*/
int sjf_HeapIncreaseKey(sjf_rq_ptr heap, int index, process_ptr key) {
    heap->job_priority_q[index] = key;
    while (index>0 && sjf_compare(heap->job_priority_q[index], heap->job_priority_q[parent(index)])){  //compare function is needed for other data type.
        sjf_swap(heap->job_priority_q[index], heap->job_priority_q[parent(index)]);
        index = sjf_parent(index);
    }
    return 1;
}

/*
    Insert process to job queue
*/
void sjf_Insert(sjf_rq_ptr heap, process_ptr key) {
    heap->size++;
    sjf_HeapIncreaseKey(heap, (heap->size) -1, key);
}

process_ptr sjf_HeapExtractMax(sjf_rq_ptr heap) {
    if (heap->size <0) {
        printf("Error: Heap underflow");
        return -1;
    }
    process_ptr max = heap->job_priority_q[0];
    heap->job_priority_q[0] = heap->job_priority_q[(heap->size) - 1];
    heap->size--;
    sjf_Heapify(heap, 0);
    return max;
}

process_ptr sjf_HeapMax(sjf_rq_ptr heap) {
    return heap->job_priority_q[0];
}


sjf_rq_ptr init_sjf_ready_q(sjf_rq_ptr sjf_rq_addr){
    sjf_rq_addr = (sjf_rq_ptr)malloc(sizeof(sjf_rq));
    //Initialize sjf ready queue
    for(int i=0; i<PROC_NUM; i++){
        sjf_rq_addr->job_priority_q[i] = 0;
    }
    sjf_rq_addr->size = 0;
    
    return sjf_rq_addr;
}

#endif