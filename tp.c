#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char* temp[2];
    temp[0] = "gedit";
    temp[1] = NULL;

    if (execvp(temp[0], temp) == -1)
    {
        printf("error");
    }
    else
    {
        printf("yay");
    }
    
    return 0;
}