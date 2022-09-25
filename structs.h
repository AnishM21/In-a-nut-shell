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
struct process* bg_process_list;

void updateProcList(char* name, int pid);
void deleteProc();
void