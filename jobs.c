#include "jobs.h"
#include "structs.h"

extern char command[100][1000];
extern int comm_count, global_bg_count;

int comparator_function(const void* s1, const void* s2)
{
    struct process *a = (struct process*) s1, *b = (struct process*) s2;

    if (strcmp(a->proc_name, b->proc_name) == 0)
    {
        if (a->job_num > b->job_num)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    return strcmp(a->proc_name, b->proc_name);
}

void jobs()
{
    int s_flag = 0, r_flag = 0;
    for (int i = 0; i < comm_count; i++)
    {
        if (strcmp(command[i], "-s") == 0)
        {
            s_flag = 1;
        }
        else if (strcmp(command[i], "-r") == 0)
        {
            r_flag = 1;
        }
    }
    if (r_flag == 1)
    {
        struct process* trav = proc_list_head;
        while (trav != NULL)
        {
            char proc_file[64];
            sprintf(proc_file, "/proc/%d/stat", trav->pid);
            FILE* file_desc = fopen(proc_file, "r");

            char str[10];
            for (int i = 0; i < 3; i++)
            {
                fscanf(file_desc,"%s", str);
            }
            if (strcmp(str, "R")==0 || strcmp(str, "S")==0)
            {
                printf("[%d] Running %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
            }
            trav = trav->next;
        }
    }
    else if (s_flag == 1)
    {
        struct process* trav = proc_list_head;
        while (trav != NULL)
        {
            char proc_file[64];
            sprintf(proc_file, "/proc/%d/stat", trav->pid);
            FILE* file_desc = fopen(proc_file, "r");

            char str[10];
            for (int i = 0; i < 3; i++)
            {
                fscanf(file_desc,"%s", str);
            }
            if (strcmp(str, "T")==0)
            {
                printf("[%d] Running %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
            }
            trav = trav->next;
        }
    }
    else
    {
        struct process* trav = proc_list_head;
        while (trav != NULL)
        {
            char proc_file[64];
            sprintf(proc_file, "/proc/%d/stat", trav->pid);
            FILE* file_desc = fopen(proc_file, "r");

            char str[10];
            for (int i = 0; i < 3; i++)
            {
                fscanf(file_desc,"%s", str);
            }
            if (strcmp(str, "R")==0 || strcmp(str, "S")==0)
            {
                printf("[%d] Running %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
            }
            else if (strcmp(str, "T")==0)
            {
                printf("[%d] Stopped %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
            }
            trav = trav->next;
        }
    }
}