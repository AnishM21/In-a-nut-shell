#include "foreground.h"

void f2(char process[][1000], int n) {
    // printf("%d      ", n);
    char* temp[100];
    for (int i = 0; i < n; i++) {
        if (strcmp(process[i], ">") == 0 || strcmp(process[i], "<") == 0 || strcmp(process[i], ">>") == 0) {
            continue;
        }
        temp[i] = process[i];
        // printf("%s\n", temp[i]);
    }
    temp[n] = NULL;
    float timer = 0.0;
    time_t start = time(NULL);
    pid_t pid = fork();

    // char* temp[100];
    // for (int i = 0; i < n; i++)
    // {
    //     temp[i] = process[i];
    //     // printf("%s\n", temp[i]);
    // }
    // temp[n] = NULL;

    // printf("%d\n", pid);

    if (pid < 0) {
        printf("Error creating process\n");
    } else if (pid == 0) {
        if (execvp(temp[0], temp) == -1) {
            printf("The given process was undefined\n");
        }
        // printf("R2\n");
    } else {
        // printf("R3\n");
        waitpid(pid, NULL, WUNTRACED);
        // printf("R4\n");
        time_t end = time(NULL);
        timer = end - start;
        if (timer > 1) {
            printf("Took %.1fs\n", timer);
        }
    }
}