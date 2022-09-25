#include "foreground.h"

void fore(char process[][1000], int n) {
    // printf("Entered function\n");
    char* temp[100];
    for (int i = 0; i < n; i++) {
        temp[i] = process[i];
    }
    temp[n] = NULL;
    float timer = 0.0;
    time_t begin = time(NULL);
    pid_t pid = fork();

    if (pid < 0) {
        printf("Error in creating process\n");
    } else if (pid == 0) {
        if (execvp(temp[0], temp) == -1) {
            printf("The given process was undefined\n");
        }
        // exit(0);
    } else {
        // printf("Reached here\n");
        waitpid(pid, NULL, WUNTRACED);
        time_t end = time(NULL);
        timer = (end - begin);
        if (timer > 1) {
            printf("took %.1fs\n", timer);
        }
    }
}
