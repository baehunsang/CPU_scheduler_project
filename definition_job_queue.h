#ifndef JOB_QUEUE
#define JOB_QUEUE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"

typedef struct JQ
{
    process_ptr job_priority_q[PROC_NUM];
    int size;
}jq;
typedef jq* jq_ptr;
/*
    swap each processes data
    [in]process1's address
    [in]process2's address
*/
void swap(process_ptr element1, process_ptr element2) {
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
int parent(int index) {
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
int compare(process_ptr process1, process_ptr process2){
    if(process1->arrival_time < process2->arrival_time){
        return 1;
    }
    if(process1->arrival_time == process2->arrival_time){
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
void Heapify(jq_ptr heap, int index) { //Top to Down 
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int largest = index;                   //Making max-heap
    if (leftIndex <= (heap->size) - 1 &&
        compare(heap->job_priority_q[leftIndex] , heap->job_priority_q[largest])) {              //compare function is needed in here
        largest = leftIndex;
    } // compare left node
    if (rightIndex <= (heap->size) - 1 &&
        compare(heap->job_priority_q[rightIndex], heap->job_priority_q[largest])) {
        largest = rightIndex;
    }// compare right node
    if (largest != index) {
        swap(heap->job_priority_q[index], heap->job_priority_q[largest]); // swap
        Heapify(heap, largest);   // reculsive action, untile last level
    }
}

/*
    Executed each insertion sorting job priority queue.
*/
int HeapIncreaseKey(jq_ptr heap, int index, process_ptr key) {
    heap->job_priority_q[index] = key;
    while (index>0 && compare(heap->job_priority_q[index], heap->job_priority_q[parent(index)])){  //compare function is needed for other data type.
        swap(heap->job_priority_q[index], heap->job_priority_q[parent(index)]);
        index = parent(index);
    }
    return 1;
}

/*
    Insert process to job queue
*/
void Insert(jq_ptr heap, process_ptr key) {
    heap->size++;
    HeapIncreaseKey(heap, (heap->size) -1, key);
}

process_ptr HeapExtractMax(jq_ptr heap) {
    if (heap->size <0) {
        printf("Error: Heap underflow");
        return -1;
    }
    process_ptr max = heap->job_priority_q[0];
    heap->job_priority_q[0] = heap->job_priority_q[(heap->size) - 1];
    heap->size--;
    Heapify(heap, 0);
    return max;
}

process_ptr HeapMax(jq_ptr heap) {
    return heap->job_priority_q[0];
}


jq_ptr init_jq(jq_ptr jq_addr){
    jq_addr = (jq_ptr)malloc(sizeof(jq));
    //Initialize job queue
    for(int i=0; i<PROC_NUM; i++){
        jq_addr->job_priority_q[i] = 0;
    }
    jq_addr->size = 0;
    
    return jq_addr;
}

#endif