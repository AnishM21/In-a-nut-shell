#include "echo.h"

void echo(char arr[][1000], int num) {
    // strtok(arr, " ");
    // char *buffer = strtok(NULL, "\0");

    // printf("%s", buffer);

    for (int i = 1; i < num; i++) {
        if (strcmp(arr[i], ">") == 0 || strcmp(arr[i], "<") == 0 || strcmp(arr[i], ">>") == 0) {
            break;
        } else {
            printf("%s ", arr[i]);
        }
    }
    printf("\n");
}