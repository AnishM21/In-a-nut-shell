#include "structs.h"

extern int global_bg_count;

void updateProcList(char* name, int pid) {
    struct process* trav = bg_process_list;
    while (trav->next != NULL) {
        trav = trav->next;
    }

    struct process* temp_node = (struct process*)malloc(sizeof(struct process));
    temp_node->pid = pid;
    strcpy(temp_node->proc_name, name);
    temp_node->job_num = global_bg_count;

    trav->next = temp_node;
    temp_node->next = NULL;
}

void deleteProc(int req_pid)
{
    struct process* trav = bg_process_list;
    struct process* check = trav->next;
    while (trav->next != NULL)
    {
        if (check->pid == req_pid && check!=NULL)
        {
            trav->next = check->next;
            free(check);
        }
        else
        {
            trav = check;
            check = check->next;
        }
    }
}

