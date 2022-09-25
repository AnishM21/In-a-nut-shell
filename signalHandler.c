#include "signalHandler.h"

#include <stdbool.h>
#include <sys/utsname.h>

#include "foreground.h"
#include "pinfo.h"
#include "prompt.h"

extern char proc[100][1000];
extern long bg_counter, proc_pid[100];
extern char decoy_pseudo_dir[1000], command[100][1000];

void bg_signal_handler(int sig) {
    char pr_name[50];
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid == -1) {
        return;
    }
    // strcpy(pr_name, proc_name(pid));
    for (int i = 0; i < 100; i++) {
        if (proc_pid[i] == pid) {
            strcpy(pr_name, proc[i]);
            break;
        }
    }

    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            printf("process %s with pid %d exited normally\n", pr_name, pid);
            bg_counter--;
        } else {
            printf("process %s with pid %d exited abnormally\n", pr_name, pid);
            bg_counter--;
        }
    }
}

void cntrl_C_handler(int sig) {
    printf("\n");
    prompt();
    fflush(stdout);
}

void cntrl_Z_handler(int sig) {
}