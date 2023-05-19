#ifndef LOG_LIST
#define LOG_LIST
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./process.h"

typedef struct process_log{
    int process_id;
    int start_time;
    int turnaround_time;
}process_log;

typedef process_log* process_log_ptr;

typedef struct process_log_list{
    process_log_ptr list;
    int size;
    int capacity;
}process_log_list;

typedef process_log_list* process_log_list_ptr;

/*
    initialize log list
*/
process_log_list_ptr init_log_list(process_log_list_ptr addr){
    addr = (process_log_list_ptr)malloc(sizeof(process_log_list));
    addr->list = NULL;
    addr->size = 0;
    addr->capacity = 1;
    return addr;
}

/*
    if context switch accure, insert process into log list
*/
int insert_log(process_log_list_ptr log_list, int process_id,int start_time, int turnaround_time){
    if(log_list->size == 0){
        log_list->list = (process_log_ptr)malloc(sizeof(process_log));
    }
    log_list->list[log_list->size].process_id = process_id;
    log_list->list[log_list->size].turnaround_time = turnaround_time;
    log_list->list[log_list->size].start_time = start_time;
    log_list->size++;

    if(log_list->size == log_list->capacity){
        log_list->capacity *= 2;
        log_list->list = (process_log_ptr)realloc(log_list->list, sizeof(process_log)*log_list->capacity);
    }

    return 0;
}

/*
    this is for debuging. print log list
*/
void print_log(process_log_list_ptr log_list){
    for(int i =0; i< log_list->size; i++){
        printf("P%d scheduled at: %d , terminated at: %d\n", log_list->list[i].process_id, log_list->list[i].start_time, log_list->list[i].turnaround_time);
    }
}

void destroy_log(process_log_list_ptr log_list){
    free(log_list->list);
    free(log_list);
}







#endif