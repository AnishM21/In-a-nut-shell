#include "pinfo.h"

extern char decoy_pseudo_dir[1000];

void pinfo_blank()
{
    pid_t pid = getpid(); // To get the PID of the process
    char process_status[1000], exe_file[1000]; // To get the process status codes of given PID
    strcpy(process_status, "/proc/");
    strcpy(exe_file, "/proc");
    sprintf(exe_file, "/proc/%d/exe", pid);
    sprintf(process_status, "/proc/%d", pid);
    strcat(process_status, "/stat");

    // printf("%s\n", process_status);
    printf("%s\n", exe_file);

    FILE *file_ptr = fopen(process_status, "r");

    if (file_ptr == NULL)
    {
        // printf("There was an error in opening the file\n");
        perror("Error");
    }
    else
    {
        char pid_s[20], processState[10], memory[50], path[100], temp1[10], temp2[10], gen[1000];
        for (int i = 0; i < 25; i++)
        {
            // fscanf(file_ptr, "%s", gen);
            // printf("%d %s\n", i, gen);
            if (i == 4)
            {
                // printf("Reached here\n");
                fscanf(file_ptr, "%s", temp1);
            }
            else if (i == 7)
            {
                fscanf(file_ptr, "%s", temp2);
            }
            else if (i == 1)
            {
                fscanf(file_ptr, "%s", path);
            }
            else if (i == 2)
            {
                fscanf(file_ptr, "%s", processState);
            }
            else if (i == 0)
            {
                fscanf(file_ptr, "%s", pid_s);
            }
            else if (i == 22)
            {
                fscanf(file_ptr, "%s", memory);
            }
            else
            {
                fscanf(file_ptr, "%s", gen);
            }
        }
        // printf("%s %s\n", temp1, temp2);

        char buff[1000];
        char copy[1000];
        bool finish = true;
        int path_check = readlink(exe_file, buff, 1000);

        if (path_check == -1)
        {
            perror("Path does not exist:");

        }
        else
        {
            for (int i = 0; i < strlen(decoy_pseudo_dir); i++)
            {
                if (buff[i] != decoy_pseudo_dir[i])
                {
                    finish = false;
                    break;
                }
            }
            if (finish == true)
            {
                int u = 1;
                strcpy(copy, "~");
                for (int i = strlen(decoy_pseudo_dir); i < strlen(buff); i++)
                {
                    copy[u] = buff[i];
                    u++;
                }
                // printf("%s\n", copy);
            }
        }

        if (strcmp(temp1, temp2) == 0)
        {
            strcat(processState, "+");
        }
        printf("pid : %s\n", pid_s);
        printf("process status : %s\n", processState);
        printf("memory : %s\n", memory);
        printf("executable path : ");
        if (finish)
        {
            printf("%s\n", copy);
        }
        else
        {
            printf("%s\n", buff);
        }
    }
}

void pinfo_pid(int pid)
{
    // pid_t pid = getpid(); //To get the PID of the process

    char process_status[1000], exe_file[1000]; // To get the process status codes of given PID
    strcpy(process_status, "/proc/");
    strcpy(exe_file, "/proc");
    sprintf(exe_file, "/proc/%d/exe", pid);
    sprintf(process_status, "/proc/%d", pid);
    strcat(process_status, "/stat");

    // printf("%s\n", process_status);
    printf("%s\n", exe_file);

    FILE *file_ptr = fopen(process_status, "r");

    if (file_ptr == NULL)
    {
        // printf("There was an error in opening the file\n");
        perror("Error");
    }
    else
    {
        char pid_s[20], processState[10], memory[50], path[100], temp1[10], temp2[10], gen[1000];
        for (int i = 0; i < 25; i++)
        {
            if (i == 4)
            {
                fscanf(file_ptr, "%s", temp1);
            }
            else if (i == 7)
            {
                fscanf(file_ptr, "%s", temp2);
            }
            else if (i == 1)
            {
                fscanf(file_ptr, "%s", path);
            }
            else if (i == 2)
            {
                fscanf(file_ptr, "%s", processState);
            }
            else if (i == 0)
            {
                fscanf(file_ptr, "%s", pid_s);
            }
            else if (i == 22)
            {
                fscanf(file_ptr, "%s", memory);
            }
            else
            {
                fscanf(file_ptr, "%s", gen);
            }
        }
        
        // executable path
        char buff[512];
        char copy[512];
        bool finish = true;
        int path_check = readlink(exe_file, buff, 512);

        if (path_check == -1)
        {
            perror("Path does not exist:");

        }
        else
        {
            
            for (int i = 0; i < strlen(decoy_pseudo_dir); i++)
            {
                if (buff[i] != decoy_pseudo_dir[i])
                {
                    finish = false;
                    break;
                }
            }
            if (finish)
            {
                int u = 1;
                strcpy(copy, "~");
                for (int i = strlen(decoy_pseudo_dir); i < strlen(buff); i++)
                {
                    copy[u] = buff[i];
                    u++;
                }
            }
        }

        // printf("%s %s\n", temp1, temp2);
        if (strcmp(temp1, temp2) == 0)
        {
            strcat(processState, "+");
        }
        printf("pid : %s\n", pid_s);
        printf("process status : %s\n", processState);
        printf("memory : %s\n", memory);
        printf("executable path : ");
        (finish == true) ? printf("%s\n", copy) : printf("%s\n", buff);
    }
}

// char* proc_name(int pid)
// {
//     char process_status[1000]; // To get the process status codes of given PID
//     strcpy(process_status, "/proc/");
//     sprintf(process_status, "/proc/%d", pid);
//     strcat(process_status, "/stat");

//     FILE *file_ptr = fopen(process_status, "r");

//     if (file_ptr == NULL)
//     {
//         printf("There was an error in opening the file\n");
//     }

//     char* gen = (char*)malloc(50 * sizeof(char));
//     char temp[50];
//     for (int i = 0; i < 2; i++)
//     {
//         fscanf(file_ptr, "%s", temp);
//     }
//     int u = 0;
//     for (int i = 0; i < strlen(temp)-1; i++)
//     {
//         gen[u] = temp[i];
//     }
//     return gen;
// }

