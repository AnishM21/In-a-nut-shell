#include "foreground.h"
#include "prompt.h"
#include "structs.h"

char proc[100][1000];
long bg_counter = 0, proc_pid[100];
int global_bg_count = 0;

void bg(char process[][1000], int n) {
    char* temp[100];
    for (int i = 0; i < n; i++) {
        temp[i] = process[i];
    }
    temp[n] = NULL;

    pid_t pid = fork();
    // printf("%d\n", pid);

    if (pid < 0) {
        printf("Error in creating process\n");
    } else if (pid == 0) {
        setpgid(0, 0);
        if (execvp(temp[0], temp) == -1) {
            perror("Illegal command:");
            exit(0);
            // printf("The given process was undefined\n");
        }
        // printf("Executed\n");
        // exit(0);
    } else {
        setpgid(pid, pid);
        global_bg_count++;
        printf("[%ld] %d\n", bg_counter + 1, pid);
        updateProcList(temp[0], pid);
        strcpy(proc[bg_counter % 100], temp[0]);
        proc_pid[bg_counter % 100] = pid;
        // bg_counter++;
    }
}