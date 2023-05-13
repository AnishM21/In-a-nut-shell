#include "piping.h"
#include "execute.h"
#include "redirection.h"

extern char input[1000][1000];
char pipe_arguments[100][1000];
// extern int com_count;


void checkPipes(int i)
{
    printf("Reached here\n");
    int input_fd_original = dup(STDIN_FILENO);
    int output_fd_original = dup(STDOUT_FILENO);
    int input_fd = 0;

    int pipe_num = 0;
    char delim[1] = {'|'};
    char temp_input[1000];
    strcpy(temp_input, input[i]);

    printf("%s\n", input[i]);
    char *temp = strtok(temp_input, delim);

    if (strcmp(temp,input[i]) == 0)
    {
        return;
    }

    while (temp != NULL)
    {
        pipe_num++;
        printf("%s\n", temp);
        strcpy(pipe_arguments[pipe_num], temp);
        temp = strtok(NULL, delim);
    }
    printf("%d - pipenum\n", pipe_num);
    int pipe_array[pipe_num][2];

    for (int i = 0; i < pipe_num; i++)
    {
        printf("entered loop\n");
        if (pipe(pipe_array[i]) < 0)
        {
            printf("Error creating pipes\n");
        }

        char delim[4] = {' ','\t'};
        temp_com_count = 0;
        char *t_arg = strtok(pipe_arguments[i], delim);
        while (t_arg != NULL)
        {
            strcpy(temp_command[temp_com_count], t_arg);
            t_arg = strtok(NULL, delim);
            temp_com_count++;
        }

        int redi_flag = 0;
        // for (int j = 0; j < temp_com_count; j++)
        // {
        //     if (strcmp(temp_command[j], ">") == 0 || strcmp(temp_command[j], "<") == 0 || strcmp(temp_command[j], ">>") == 0)
        //     {
        //         // printf("Entered here\n");
        //         redirection_piping();
        //         redi_flag = 1;
        //         break;
        //     }
        // }

        if (!redi_flag)
        {
            dup2(input_fd, 0);
            if (i < pipe_num - 1)
            {
                dup2(pipe_array[i][1], 1);
            }
            else
            {
                dup2(output_fd_original, 1);
            }
            execute_piping();
            close(pipe_array[i][1]);
            input_fd = pipe_array[i][0];
        }
    }
    dup2(input_fd_original, 0);
}