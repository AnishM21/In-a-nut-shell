#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct process {
    char proc_name[100];
    int pid;
    int job_num;
    struct process* next;
};

struct process fg_process;
struct process* proc_list_head;
struct process* proc_list_next;

void updateProcList(char* name, int pid);
void deleteProc(int req_pid);
struct process* getProcNameFromPID(int req_pid);
struct process* getProcNameFromJobNum(int req_job_num);
void processStatus(int req_pid);
void processStatus_SFlag(int req_pid);
void processStatus_RFlag(int req_pid);
void printProcList();

#endif