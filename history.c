#include "history.h"

// void updateHistory(char *arr, char** historyArr, int pos, int tot)
// {
//     printf("%d\n", pos);
//     if (tot == 1)
//     {
//         printf("Stage 4\n");
//         historyArr[pos] = arr;
//         // strcpy(historyArr[pos], arr);
//         printf("%s %d\n", historyArr[pos], pos);
//         return;
//     }

//     else if (pos > 0)
//     {
//         printf("Stage 2\n");
//         for (int i = 0; i < pos; i++)
//         {
//             printf("%s\n", historyArr[i]);
//         }

//         if (strcmp(historyArr[pos-1], arr) == 0)
//         {
//             printf("%s - %s\n", historyArr[pos-1], arr);
//             printf("being returned\n");
//             return;
//         }
//         else
//         {
//             // strcpy(historyArr[pos], arr);
//             historyArr[pos] = arr;
//             printf("%s\n", historyArr[pos]);
//         }
//     }
//     else
//     {
//         printf("Stage 3\n");
//         if (historyArr[19] == arr)
//         {
//             return;
//         }
//         else
//         {
//             // strcpy(historyArr[pos], arr);
//             historyArr[pos] = arr;
//             printf("%s\n", historyArr[pos]);
//         }
//     }
// }
char history[20][1000];
int current_position = 0;
int previous_position = -1;
// char hist_file_loc[1000];

void readFromFile(char* hist_file_loc)
{
    FILE* file_ptr = fopen(hist_file_loc, "r");
    char* temp;
    for (int i = 0; i < 20; i++)
    {
        fscanf(file_ptr, " %[^\n]s", temp);
        strcpy(history[i], temp);
    }
    fclose(file_ptr);
}

void updateHistory(char *inputCommand, int *tot)
{
    // FILE *file_ptr = fopen("history.txt", "w");

    if (tot == 0)
    {
        strcpy(history[current_position], inputCommand);
    }
    else if (strcmp(history[previous_position], inputCommand) == 0)
    {
        *tot++;
        return;
    }
    else
    {
        strcpy(history[current_position], inputCommand);
    }

    // for (int i = current_position; i < 20 + current_position; i++)
    // {
    //     printf("%d %d\n", current_position, i%20);
    //     printf("%s\n", history[i%20]);
    //     fprintf(file_ptr, "%s", history[i%20]);
    // }
    // fprintf(file_ptr, "\n");
    // fclose(file_ptr);
    // // printf("%d\n", current_position%20);
    // // fprintf(file_ptr, "%s\n", history[current_position%20]);

    // // for (int i = 0; i < 20; i++)
    // // {
    // //     printf("%s\n", history[i]);
    // // }
    tot++;
    previous_position++;
    previous_position %= 20;
    current_position++;
    current_position %= 20;
}

void historyCheck()
{
    for (int i = 0; i < 20; i++)
    {
        printf("%s\n", history[i]);
    }
}

void updateToFile(char* hist_file_loc)
{
    FILE* file_ptr = fopen(hist_file_loc, "w");
    for (int i = current_position; i < 20+current_position; i++)
    {
        if (strcmp(history[i%20]," ") != 0)
        {
            // printf("%s\n", history[i%20]);
            fprintf(file_ptr, "%s\n", history[i%20]);
        }
        // fprintf(file_ptr, "%s\n", history[i%20]);
    }
    fclose(file_ptr);
}

void printHistory()
{
    if (current_position >= 10)
    {
        for (int i = current_position-10; i < current_position; i++)
        {
            printf("%s\n", history[i]);
        }
    }
    else
    {
        // int n = 9 - current_position;
        // for (int i = 20-n; i < 20; i++)
        // {
        //     printf("%s\n", history[i]);
        // }
        // for (int i = 0; i < current_position; i++)
        // {
        //     printf("%s\n", history[i]);
        // }  
        for (int i = current_position-10; i < current_position; i++)
        {
            if (i < 0)
            {
                printf("%s\n", history[(20+i)%20]);
            }
            else
            {
                printf("%s\n", history[i]);
            }
        }
    }
}


// void printHistory(char **historyArr, int numberOfCommands, int tot_commands)
// {
//     int len = 20;
//     printf("The number of commands in the history arr are - %d\n", len);
//     if (numberOfCommands > 20 || numberOfCommands > len) // If the total number of commands the history function wants to print is more than 20 returns error
//     {
//         printf("Too many commands have been asked. Please input a number between 0 and 20\n");
//     }
//     else
//     {
//         if (numberOfCommands == 0) // If only history command specified without number, assumed to be 10, checks if total commands in session are more than 10 or no
//         {
//             int temp = tot_commands % 20;
//             if (tot_commands >= 10)
//             {
//                 for (int i = temp - 10; i < temp; i++)
//                 {
//                     printf("%d %s\n", i, historyArr[i]);
//                 }
//             }
//             else
//             {
//                 for (int i = 0; i < temp; i++)
//                 {
//                     printf("%d %s\n", i, historyArr[i]);
//                 }
//             }
//         }
//         else
//         {
//             for (int i = len - numberOfCommands; i < len; i++)
//             {
//                 printf("%d %s\n", i, historyArr[i]);
//             }
//         }
//     }
// }
