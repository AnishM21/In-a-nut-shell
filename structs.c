#include "structs.h"

extern int global_bg_count;
long bg_counter;

void updateProcList(char *name, int pid)
{
    if (proc_list_head == NULL)
    {
        // printf("First step for updating\n");
        struct process *temp_node = (struct process *)malloc(sizeof(struct process));
        temp_node->pid = pid;
        strcpy(temp_node->proc_name, name);
        temp_node->job_num = global_bg_count;

        proc_list_head = temp_node;
        proc_list_next = proc_list_head;
        proc_list_next->next = NULL;
        bg_counter++;
        return;
    }
    else
    {
        // printf("adding to previous processes\n");
        struct process *temp_node = (struct process *)malloc(sizeof(struct process));
        temp_node->pid = pid;
        strcpy(temp_node->proc_name, name);
        temp_node->job_num = global_bg_count;

        proc_list_next->next = temp_node;
        proc_list_next = proc_list_next->next;
        proc_list_next->next = NULL;
        bg_counter++;
        // printProcList();
    }
}

void deleteProc(int req_pid)
{
    struct process *trav = proc_list_head;
    struct process *trav_next = proc_list_head->next;
    if (proc_list_head->pid == req_pid)
    {
        proc_list_head = proc_list_head->next;
        free(trav);
        bg_counter--;
        if (bg_counter == 0)
        {
            global_bg_count = 0;
        }
        return;
    }
    else
    {
        while (trav->next != NULL)
        {
            if (trav_next->pid == req_pid && trav_next != NULL)
            {
                trav->next = trav->next->next;
                free(trav_next);
                bg_counter--;
                // printProcList();
                return;
            }
            trav = trav->next;
            trav_next = trav_next->next;
        }
    }
    printf("The process was not found\n");
}

struct process *getProcNameFromPID(int req_pid)
{
    struct process *trav = proc_list_head;

    while (trav != NULL)
    {
        if (trav->pid == req_pid)
        {
            return trav;
        }
        trav = trav->next;
    }
    return NULL;
}

struct process *getProcNameFromJobNum(int req_job_num)
{
    struct process *trav = proc_list_head;

    while (trav != NULL)
    {
        if (trav->job_num == req_job_num)
        {
            return trav;
        }
        trav = trav->next;
    }
    return NULL;
}

// void processStatus(int req_pid)
// {
//     struct process *trav = proc_list_head;
//     while (trav != NULL)
//     {
//         if (trav->pid == req_pid)
//         {
//             char proc_file[1000];
//             sprintf(proc_file, "/proc/%d/status", req_pid);
//             FILE *file_stat = fopen(proc_file, "r");

//             if (file_stat == NULL)
//             {
//                 return;
//             }
//             char str[10];
//             for (int i = 0; i < 3; i++)
//             {
//                 fscanf(file_stat, "%s", str);
//             }
//             if (strcmp(str, "R") == 0 || strcmp(str, "S") == 0)
//             {
//                 printf("[%d] Running %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
//             }

//             else if (strcmp(str, "T") == 0)
//             {
//                 printf("[%d] Stopped %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
//             }
//         }
//     }
// }

// void processStatus_RFlag(int req_job_num)
// {
//     struct process *trav = proc_list_head;
//     while (trav != NULL)
//     {
//         if (trav->job_num == req_job_num)
//         {
//             char proc_file[1000];
//             sprintf(proc_file, "/proc/%d/status", trav->pid);
//             FILE *file_stat = fopen(proc_file, "r");

//             if (file_stat == NULL)
//             {
//                 return;
//             }
//             char str[10];
//             for (int i = 0; i < 3; i++)
//             {
//                 fscanf(file_stat, "%s", str);
//             }
//             if (strcmp(str, "R") == 0 || strcmp(str, "S") == 0)
//             {
//                 printf("[%d] Running %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
//             }

//             // else if (strcmp(str, "T") == 0)
//             // {
//             //     printf("[%d] Stopped %s [%d]\n", trav->job_num, trav->proc_name, trav->pid);
//             // }
//         }
//     }

// }

void printProcList()
{
    struct process *trav = proc_list_head;
    while (trav != NULL)
    {
        printf("%s\n", trav->proc_name);
        trav = trav->next;
    }
}