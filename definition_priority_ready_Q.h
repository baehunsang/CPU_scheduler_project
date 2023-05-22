#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"

typedef struct PRIORITY_RQ
{
    process_ptr job_priority_q[PROC_NUM];
    int size;
}priority_rq;
typedef priority_rq* priority_rq_ptr;
/*
    swap each processes data
    [in]process1's address
    [in]process2's address
*/
void priority_swap(process_ptr element1, process_ptr element2) {
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
int priority_parent(int index) {
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
int priority_compare(process_ptr process1, process_ptr process2){
    if(process1->priority > process2->priority){
        return 1;
    }
    if(process1->priority == process2->priority){
        if(process1->pid > process2->pid){
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
void priority_Heapify(priority_rq_ptr heap, int index) { //Top to Down 
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int largest = index;                   //Making max-heap
    if (leftIndex <= (heap->size) - 1 &&
        priority_compare(heap->job_priority_q[leftIndex] , heap->job_priority_q[largest])) {              //compare function is needed in here
        largest = leftIndex;
    } // compare left node
    if (rightIndex <= (heap->size) - 1 &&
        priority_compare(heap->job_priority_q[rightIndex], heap->job_priority_q[largest])) {
        largest = rightIndex;
    }// compare right node
    if (largest != index) {
        priority_swap(heap->job_priority_q[index], heap->job_priority_q[largest]); // swap
        priority_Heapify(heap, largest);   // reculsive action, untile last level
    }
}

/*
    Executed each insertion sorting job priority queue.
*/
int priority_HeapIncreaseKey(priority_rq_ptr heap, int index, process_ptr key) {
    heap->job_priority_q[index] = key;
    while (index>0 && priority_compare(heap->job_priority_q[index], heap->job_priority_q[priority_parent(index)])){  //compare function is needed for other data type.
        priority_swap(heap->job_priority_q[index], heap->job_priority_q[priority_parent(index)]);
        index = priority_parent(index);
    }
    return 1;
}

/*
    Insert process to job queue
*/
void priority_Insert(priority_rq_ptr heap, process_ptr key) {
    heap->size++;
    priority_HeapIncreaseKey(heap, (heap->size) -1, key);
}

process_ptr priority_HeapExtractMax(priority_rq_ptr heap) {
    if (heap->size <0) {
        printf("Error: Heap underflow");
        return -1;
    }
    process_ptr max = heap->job_priority_q[0];
    heap->job_priority_q[0] = heap->job_priority_q[(heap->size) - 1];
    heap->size--;
    priority_Heapify(heap, 0);
    return max;
}

process_ptr priority_HeapMax(priority_rq_ptr heap) {
    return heap->job_priority_q[0];
}


priority_rq_ptr init_priority_ready_q(priority_rq_ptr priority_rq_addr){
    priority_rq_addr = (priority_rq_ptr)malloc(sizeof(priority_rq));
    //Initialize sjf ready queue
    for(int i=0; i<PROC_NUM; i++){
        priority_rq_addr->job_priority_q[i] = 0;
    }
    priority_rq_addr->size = 0;
    
    return priority_rq_addr;
}

#endif