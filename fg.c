#include "fg.h"
#include "structs.h"

extern char command[100][1000];
extern int comm_count;

void fg()
{
    if (comm_count != 2)
    {
        printf("Invalid number of arguments\n");
    }
    else
    {
        int job_number_temp = atoi(command[1]);
        struct process *trav = proc_list_head;
        while (trav != NULL)
        {
            if (trav->job_num == job_number_temp)
            {
                kill(trav->pid, SIGCONT);
                int child_pid = trav->pid;
                fg_process.job_num = 1;
                fg_process.pid = trav->pid;
                strcpy(fg_process.proc_name, trav->proc_name);
                fg_process.next = NULL;
                deleteProc(child_pid);
                waitpid(-1, NULL, WUNTRACED);
                return;
            }
            trav = trav->next;
        }
        if (trav == NULL)
        {
            printf("The given process does not exist\n");
        }
    }
}

void bg2()
{
    if (comm_count != 2)
    {
        printf("Invalid number of arguments\n");
    }
    else
    {
        int job_number_temp = atoi(command[1]);
        struct process *trav = proc_list_head;
        while (trav != NULL)
        {
            if (trav->job_num == job_number_temp)
            {
                kill(trav->pid, SIGTTIN);
                kill(trav->pid, SIGCONT);
                return;
            }
            trav = trav->next;
        }
        if (trav == NULL)
        {
            printf("The given process does not exist\n");
        }
    }
}