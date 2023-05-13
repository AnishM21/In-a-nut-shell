#include "sig_func.h"

extern char command[100][1000];
extern int com_count, comm_count;

void sig_func()
{
    if (comm_count != 3)
    {
        printf("Not enough arguments specified\n");
        return;
    }
    int job_number_temp = atoi(command[1]);
    int signal_number = atoi(command[2]);

    struct process *trav = proc_list_head;
    while (trav != NULL)
    {
        if (trav->job_num == job_number_temp)
        {
            kill(trav->pid, signal_number);
            // printf("Kill function executed\n");
            return;
        }
        trav = trav->next;
    }
    if (trav == NULL)
    {
        printf("The given process does not exist\n");
    }
}